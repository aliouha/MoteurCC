// =====================================================
// motor_control.h — Controleur MCC (Kalman + Retour etat)
// =====================================================

#pragma once
#include "params.h"

class MotorController {
public:

    // Etat estime [ia, wm]
    float x_hat[2] = {0.0f, 0.0f};
    float u        = 0.0f;
    float ref      = WM_REF;

    // Reset
    void reset() {
        x_hat[0] = 0.0f;
        x_hat[1] = 0.0f;
        u        = 0.0f;
    }

    // Mise a jour Kalman + commande
    // y_meas = wm mesuree (rad/s)
    // Retourne alpha PWM [0, 1]
    float update(float y_meas) {

        // 1. Innovation
        float innov = y_meas - x_hat[1];

        // 2. Prediction modele discret
        float x0 = AD_00*x_hat[0] + AD_01*x_hat[1] + BD_0*u + L_0*innov;
        float x1 = AD_10*x_hat[0] + AD_11*x_hat[1] + BD_1*u + L_1*innov;
        x_hat[0] = x0;
        x_hat[1] = x1;

        // 3. Loi de commande retour etat
        u = NR*ref - K_0*x_hat[0] - K_1*x_hat[1];

        // 4. Saturation tension
        if (u > VA_MAX) u = VA_MAX;
        if (u < 0.0f)  u = 0.0f;

        // 5. Saturation courant (protection)
        if (x_hat[0] > IA_MAX) x_hat[0] = IA_MAX;

        // 6. Rapport cyclique PWM
        return u / VBUS;
    }

    // Changer reference vitesse
    void setReference(float wm_ref) {
        ref = wm_ref;
    }

    // Lire etat estime
    float getIa()  { return x_hat[0]; }
    float getWm()  { return x_hat[1]; }
    float getCmd() { return u; }
};
