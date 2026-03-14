% =========================================================
%  kalman_design.m — Filtre de Kalman stationnaire
% =========================================================
run('E:\Mes-CD\Matlab-Projects\MoteurCC\params\init_params.m')

%% Matrices de bruit
Q_kal = diag([0.01, 1]);     % plus de confiance en wm
R_kal = 10;                  % bruit de mesure plus grand

%% Résolution de l'équation de Riccati
C_kal = [0 1];               % on mesure wm uniquement

[P, ~, Kf] = care(A', C_kal', Q_kal, R_kal);

% Gain de Kalman
L_kal = Kf'
fprintf('Gain Kalman L_kal =\n'); disp(L_kal)

%% Matrices observateur Kalman (même structure que Luenberger)
A_kal = A - L_kal * C_kal;
B_kal = [B, L_kal];          % 2x2
C_kal_obs = eye(2);
D_kal = zeros(2, 2);

fprintf('Pôles filtre Kalman :\n'); disp(eig(A_kal))