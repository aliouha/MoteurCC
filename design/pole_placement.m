% =========================================================
%  pole_placement.m — Calcul du gain K (retour d'état)
% =========================================================

run('E:\Mes-CD\Matlab-Projects\MoteurCC\params\init_params.m')

%% Pôles désirés
poles_desires = [-50 ; -60];

%% Calcul du gain K
K = place(A, B, poles_desires);
fprintf('Gain K = [%.4f  %.4f]\n', K(1), K(2));

%% Vérification
eig_BF = eig(A - B*K);
fprintf('Pôles boucle fermée :\n');
disp(eig_BF)

% Gain de pré-compensation (feedforward)
Nr = -1 / (C(2,:) * inv(A - B*K) * B);
fprintf('Nr = %.4f\n', Nr);