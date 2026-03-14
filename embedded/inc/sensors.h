// =====================================================
// sensors.h — Capteurs MCC (Encodeur + ACS712)
// =====================================================
#pragma once
#include "params.h"

#define PPR              1000      // Pulses Per Revolution
#define ACS712_SENS      0.066f    // V/A
#define ACS712_OFFSET    2.5f      // V
#define ADC_VREF         3.3f      // V
#define ADC_RES          4096.0f   // 12-bit

class Sensors {
public:
    float ia_offset = 0.0f;
    int32_t enc_prev = 0;

    // Calibration offset courant au demarrage
    void calibrate(float* adc_buffer, int n) {
        float sum = 0.0f;
        for (int i = 0; i < n; i++) sum += adc_buffer[i];
        ia_offset = (sum / n) * ADC_VREF / ADC_RES;
    }

    // Lecture courant ia depuis ADC (ACS712)
    float read_current(uint32_t adc_val) {
        float voltage = adc_val * ADC_VREF / ADC_RES;
        return (voltage - ACS712_OFFSET - ia_offset) / ACS712_SENS;
    }

    // Lecture vitesse depuis encodeur (rad/s)
    float read_speed(int32_t enc_count) {
        int32_t delta = enc_count - enc_prev;
        enc_prev = enc_count;
        return (float)delta / PPR * 2.0f * 3.14159f / TE;
    }
};
