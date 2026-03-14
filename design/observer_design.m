% =========================================================
%  observer_design.m — Calcul du gain L (Observateur)
% =========================================================
run('E:\Mes-CD\Matlab-Projects\MoteurCC\params\init_params.m')
run('E:\Mes-CD\Matlab-Projects\MoteurCC\design\pole_placement.m')

%% Sortie observée = wm uniquement
C_obs_in = [0 1];    % on mesure seulement wm (scalaire)

%% Pôles observateur
poles_obs = [-152.72 ; -48.605];

%% Calcul du gain L
L = place(A', C_obs_in', poles_obs)';
fprintf('Gain L =\n'); disp(L)

%% Matrices du bloc State-Space observateur
A_obs = A - L * C_obs_in;   % 2x2
B_obs = [B, L];              % [2x1 , 2x1] = 2x2 ✔
C_obs = eye(2);              % 2x2
D_obs = zeros(2, 2);         % 2x2 ✔

fprintf('A_obs =\n'); disp(A_obs)
fprintf('B_obs size : %dx%d\n', size(B_obs,1), size(B_obs,2))
fprintf('Pôles observateur :\n'); disp(eig(A_obs))