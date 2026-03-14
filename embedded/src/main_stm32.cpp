// =====================================================
// main_stm32.cpp — Controle MCC complet et robuste
// MCU  : STM32F446RE Nucleo
// PWM  : TIM1 CH1  — 20kHz
// ADC  : PA0       — courant ia (ACS712)
// ENC  : TIM2      — encodeur incremental
// ISR  : TIM6      — Te=1ms
// UART : USART2    — debug 115200
// =====================================================

#include "main.h"
#include "motor_control.h"
#include "safety.h"
#include "sensors.h"
#include "communication.h"

// Instances
MotorController ctrl;
Safety          safety;
Sensors         sensors;
Communication   com;

#define PWM_PERIOD   4200

// Variables globales
volatile bool  emergency = false;
volatile float wm_meas   = 0.0f;
volatile float ia_meas   = 0.0f;
volatile float alpha     = 0.0f;

// Reference avec rampe
float ref_ramp = 0.0f;
void update_ramp() {
    float step = 10.0f * TE;
    if (ref_ramp < ctrl.ref) ref_ramp += step;
    else ref_ramp = ctrl.ref;
    ctrl.setReference(ref_ramp);
}

// Appliquer PWM
void set_pwm(float a) {
    if (a > 1.0f) a = 1.0f;
    if (a < 0.0f) a = 0.0f;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,
        (uint32_t)(a * PWM_PERIOD));
}

// Arret urgence
void emergency_stop() {
    set_pwm(0.0f);
    ctrl.reset();
    emergency = true;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

// ISR Te=1ms — boucle de controle
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance != TIM6) return;
    if (emergency) return;

    // 1. Lecture capteurs
    ia_meas = sensors.read_current(HAL_ADC_GetValue(&hadc1));
    wm_meas = sensors.read_speed((int32_t)TIM2->CNT);

    // 2. Verification securite
    SafetyStatus st = safety.check(ia_meas, wm_meas,
                                   ctrl.getCmd());
    if (safety.isFault()) {
        emergency_stop();
        return;
    }

    // 3. Rampe reference
    update_ramp();

    // 4. Kalman + retour etat
    alpha = ctrl.update(wm_meas);

    // 5. PWM
    set_pwm(alpha);

    // 6. Watchdog
    HAL_IWDG_Refresh(&hiwdg);
}

// main()
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM6_Init();
    MX_USART2_UART_Init();
    MX_IWDG_Init();

    // Calibration capteur courant
    float calib_buf[100];
    for (int i = 0; i < 100; i++) {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 10);
        calib_buf[i] = HAL_ADC_GetValue(&hadc1);
        HAL_Delay(1);
    }
    sensors.calibrate(calib_buf, 100);

    // Demarrage
    ctrl.reset();
    ref_ramp = 0.0f;
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Base_Start_IT(&htim6);

    // Boucle principale
    char rx_buf[32];
    while (1) {
        // Debug UART
        com.send(&huart2, ctrl.getIa(),
                 ctrl.getWm(), ctrl.getCmd(),
                 safety.status);

        // Lecture nouvelle reference
        if (HAL_UART_Receive(&huart2,
            (uint8_t*)rx_buf, 32, 10) == HAL_OK) {
            float new_ref = com.parse_reference(rx_buf);
            if (new_ref > 0) ctrl.ref = new_ref;
        }

        // Reset urgence si bouton
        if (HAL_GPIO_ReadPin(BTN_GPIO_Port,
            BTN_Pin) == GPIO_PIN_RESET) {
            emergency = false;
            safety.reset();
            ctrl.reset();
            ref_ramp = 0.0f;
        }

        HAL_Delay(1);
    }
}
