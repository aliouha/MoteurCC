% =========================================================
%  init_params.m — Paramètres du Moteur à Courant Continu
%  Projet : MCC Simulation (Boucle ouverte, Retour d'état,
%           Observateur, Filtre de Kalman)
%  MATLAB 2024a
% =========================================================



%% ─── 1. PARAMÈTRES PHYSIQUES ─────────────────────────────
Ra   = 0.35;       % Résistance d'induit        [Ohm]
La   = 8.7e-3;     % Inductance d'induit         [H]
J    = 0.14;       % Moment d'inertie            [Kg.m²]
Va   = 120;        % Tension d'alimentation      [V]
Tmec = 10;         % Couple de charge            [N.m]
F    = 0.005;      % Coefficient de frottement   [N.m/rad/s]
Kphi = 0.6;        % Constante de flux           [V/rad/s]

%% ─── 2. MATRICES D'ÉTAT ──────────────────────────────────
%
%  ẋ = A*x + B*u + E*d
%  y  = C*x
%
%  x = [ia ; wm]
%  u = Va  (entrée de commande)
%  d = Tmec (perturbation)

A = [ -Ra/La,   -Kphi/La ;
       Kphi/J,  -F/J     ];

B = [ 1/La ;
      0    ];

E = [ 0    ;
     -1/J  ];

C = eye(2);        % les deux états sont mesurés : ia et wm
D = zeros(2,1);

%% ─── 3. ENTRÉE DU BLOC STATE-SPACE SIMULINK ─────────────
%  Le bloc reçoit u_vec = [Va ; Tmec]
%  donc on combine B et E en une seule matrice

B_sim = [B, E];    % taille 2x2  → entrées [Va, Tmec]
D_sim = zeros(2,2);

%% ─── 4. SIMULATION ───────────────────────────────────────
Ts     = 1e-4;     % Pas de simulation            [s]
Tfinal = 3;        % Durée totale                  [s]
x0     = [0; 0];   % Conditions initiales [ia0; wm0]

%% ─── 5. VÉRIFICATION SYSTÈME ────────────────────────────
fprintf('\n══════════════════════════════════════\n');
fprintf('   PARAMÈTRES MOTEUR MCC\n');
fprintf('══════════════════════════════════════\n');
fprintf('Ra=%.2f Ω | La=%.1f mH | J=%.2f Kg.m²\n', Ra, La*1e3, J);
fprintf('Kφ=%.2f  | F=%.4f  | Va=%d V\n', Kphi, F, Va);

fprintf('\nMatrice A :\n'); disp(A)
fprintf('Matrice B :\n'); disp(B)
fprintf('Matrice E :\n'); disp(E)

% Valeurs propres (pôles naturels du système)
poles = eig(A);
fprintf('Pôles naturels du système :\n');
fprintf('  p1 = %.4f\n', poles(1));
fprintf('  p2 = %.4f\n', poles(2));

% Vérification commandabilité & observabilité
Co = ctrb(A, B);
Ob = obsv(A, C);
fprintf('\nRang Commandabilité : %d / %d', rank(Co), size(A,1));
fprintf('\nRang Observabilité  : %d / %d\n', rank(Ob), size(A,1));

if rank(Co) == size(A,1)
    fprintf('✔ Système COMMANDABLE\n');
else
    fprintf('✘ Système NON commandable\n');
end
if rank(Ob) == size(A,1)
    fprintf('✔ Système OBSERVABLE\n\n');
else
    fprintf('✘ Système NON observable\n\n');
end