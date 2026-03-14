// =====================================================
// safety.h — Protections moteur MCC
// =====================================================
#pragma once
#include "params.h"

// Codes erreur
typedef enum {
    SAFETY_OK            = 0x00,
    SAFETY_OVERCURRENT   = 0x01,
    SAFETY_OVERVOLTAGE   = 0x02,
    SAFETY_OVERSPEED     = 0x03,
    SAFETY_EMERGENCY     = 0x04
} SafetyStatus;

class Safety {
public:
    SafetyStatus status = SAFETY_OK;
    bool enabled = true;

    SafetyStatus check(float ia, float wm, float va) {
        if (!enabled) return SAFETY_OK;
        if (ia > IA_MAX || ia < -IA_MAX)
            return status = SAFETY_OVERCURRENT;
        if (va > VA_MAX)
            return status = SAFETY_OVERVOLTAGE;
        if (wm > WM_MAX)
            return status = SAFETY_OVERSPEED;
        return status = SAFETY_OK;
    }

    bool isFault() { return status != SAFETY_OK; }
    void reset()   { status = SAFETY_OK; }
};
