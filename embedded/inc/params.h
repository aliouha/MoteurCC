// =====================================================
// params.h — Paramètres MCC générés par MATLAB
// Moteur: Ra=0.35 Ohm, La=8.7mH, J=0.14 Kg.m2
// =====================================================

#pragma once

// Periode echantillonnage
#define TE         0.0010f

// Limites moteur
#define VA_MAX     120.0f
#define IA_MAX     50.0f
#define WM_MAX     200.0f
#define VBUS       150.0f

// Modele discret Ad
#define AD_00      0.960425f
#define AD_01      -0.067592f
#define AD_10      0.004200f
#define AD_11      0.999818f

// Modele discret Bd
#define BD_0       0.112656f
#define BD_1       0.000243f

// Gain retour etat K
#define K_0        0.606689f
#define K_1        5.482028f

// Gain pre-compensation
#define NR         6.090000f

// Gain Kalman L
#define L_0        -0.011592f
#define L_1        0.008005f

// Reference vitesse
#define WM_REF     190.0f
