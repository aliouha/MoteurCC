# DC Motor Control — Commande Moteur à Courant Continu

> **Simulation & Embedded Implementation** | MATLAB/Simulink + STM32

---

## Project Overview — Vue d'ensemble

Ce projet implémente différentes stratégies de commande pour un moteur à courant continu
à excitation séparée, fonctionnant à flux constant.

**Université Hassan 1er — FST Settat | MST ATSII**

---

## Motor Parameters — Paramètres du Moteur

| Paramètre | Symbole | Valeur | Unité |
|-----------|---------|--------|-------|
| Résistance induit | Ra | 0.35 | Ω |
| Inductance induit | La | 8.7 | mH |
| Moment inertie | J | 0.14 | Kg.m² |
| Tension alimentation | Va | 120 | V |
| Couple de charge | Tmec | 10 | N.m |
| Frottement | F | 0.005 | N.m/rad/s |
| Constante de flux | Kφ | 0.6 | V/rad/s |

---

## Mathematical Model — Modèle Mathématique

### Équations différentielles

```
Va = La * (dia/dt) + Ra*ia + Kφ*wm      (circuit électrique)
Tem = J * (dwm/dt) + F*wm + Tmec         (mécanique)
Tem = Kφ * ia                             (couple électromagnétique)
```

### State-Space Representation — Représentation d'état

```
ẋ = A*x + B*u + E*d
y  = C*x

x = [ia ; wm]     (vecteur d'état)
u = Va            (entrée de commande)
d = Tmec          (perturbation)

A = [-Ra/La   -Kφ/La ]  =  [-40.23   -68.97]
    [ Kφ/J    -F/J   ]     [  4.286   -0.036]

B = [1/La]  =  [114.94]       E = [  0   ]
    [  0  ]     [  0  ]           [-1/J  ]
```

### Discrete Model — Modèle Discret (Te = 1ms, ZOH)

```
x[k+1] = Ad*x[k] + Bd*u[k]

Ad = [0.9604  -0.0676]       Bd = [0.1127]
     [0.0042   0.9998]            [0.0002]
```

---

## Control Strategies — Stratégies de Commande

### 1. Open Loop — Boucle Ouverte

```
[Va] ──► [Système] ──► [ia, wm]
```
- ia_pic ≈ 260 A | wm_régime ≈ 190 rad/s | tr ≈ 0.5s

### 2. State Feedback — Retour d'État

```
u = Nr*ref - K*x

Pôles désirés : λ1 = -50,  λ2 = -60
K  = [0.6067   5.4820]
Nr = 6.09
```
- ia_pic ≈ 900 A | wm_régime ≈ 187 rad/s | tr ≈ 0.3s

### 3. Estimated State Feedback — Retour d'État Estimé (Luenberger)

```
ẋ̂ = A*x̂ + B*u + L*(y - ŷ)       (observateur)
u  = Nr*ref - K*x̂                 (commande)

Pôles observateur : λ1 = -152.72,  λ2 = -48.605
L = [150.86]
    [161.06]
```
- Performances identiques au retour d'état réel ✔

### 4. Kalman Filter — Filtre de Kalman

```
Même structure que Luenberger — gain L optimal

Q = diag([0.01, 1])     (bruit de process)
R = 10                  (bruit de mesure)

Résolution Riccati : A'*P + P*A - P*C'*inv(R)*C*P + Q = 0

L_kal = [-0.0116]
        [ 0.0080]

Pôles Kalman : -30.54,  -9.73
```
- Robuste au bruit de mesure ✔

---

## Results — Résultats

| Strategy | ia pic (A) | wm régime (rad/s) | tr (s) |
|----------|-----------|-------------------|--------|
| Boucle ouverte | 260 | 190 | 0.5 |
| Retour d'état | 900 | 187 | 0.3 |
| Luenberger | 900 | 187 | 0.3 |
| Kalman | 900 | 187 | 0.3 |

---

## Project Structure — Structure du Projet

```
MoteurCC/
├── params/
│   └── init_params.m          # Paramètres moteur
├── models/
│   ├── MCC_boucle_ouverte.slx
│   ├── MCC_retour_etat.slx
│   ├── MCC_retour_etat_estime.slx
│   └── MCC_retour_etat_estime_Kal.slx
├── design/
│   ├── pole_placement.m       # Gain K
│   ├── observer_design.m      # Gain L Luenberger
│   ├── kalman_design.m        # Gain L Kalman
│   ├── discretisation.m       # Modèle discret
│   └── generate_code.m        # Export C++
├── scripts/
│   ├── run_boucle_ouverte.m
│   └── compare_results.m
├── embedded/
│   ├── inc/
│   │   ├── params.h           # Paramètres générés MATLAB
│   │   ├── motor_control.h    # Contrôleur Kalman
│   │   ├── safety.h           # Protections
│   │   ├── sensors.h          # Capteurs
│   │   └── communication.h    # UART debug
│   └── src/
│       └── main_stm32.cpp     # Point d'entrée STM32
├── results/
│   └── comparaison_finale.png
└── README.md
```

---

## Embedded Implementation — Implémentation Embarquée

### Hardware Stack

| Composant | Modèle | Rôle |
|-----------|--------|------|
| MCU | STM32F446RE Nucleo | Contrôleur principal |
| Capteur vitesse | Encodeur 1000 PPR | Mesure wm |
| Capteur courant | ACS712-30A | Mesure ia |
| Driver puissance | DRV8874 | Pont en H PWM |

### Control Loop — Boucle de Contrôle (Te = 1ms)

```
① Lecture capteurs  →  ia (ADC), wm (Encodeur)
② Vérification sécurité  →  surintensité, surtension, survitesse
③ Rampe référence  →  évite pic de courant au démarrage
④ Filtre Kalman  →  x̂[k+1] = Ad*x̂[k] + Bd*u[k] + L*(y-ŷ)
⑤ Loi de commande  →  u = Nr*ref - K*x̂
⑥ PWM  →  alpha = u / Vbus → TIM1
⑦ Watchdog  →  HAL_IWDG_Refresh()
```

---

## Dependencies — Dépendances

- MATLAB R2024a
- Simulink
- Control System Toolbox
- STM32CubeIDE + HAL

---

## How to Run — Lancer le Projet

```matlab
% 1. Initialisation
cd('E:\Mes-CD\Matlab-Projects\MoteurCC')
run('params/init_params.m')

% 2. Design
run('design/pole_placement.m')
run('design/observer_design.m')
run('design/kalman_design.m')

% 3. Simulation
run('scripts/compare_results.m')
```

---

*Generated with MATLAB R2024a — FST Settat*
