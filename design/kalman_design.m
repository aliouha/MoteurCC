% =========================================================
%  LQG_MoteurCC_Design.m — Script Complet Kalman + LQR
% =========================================================
% Ce script calcule L_kal (Observateur) et K_lqr (Commande)

% 1. Charger les paramètres physiques (R, L, Ke, Kt, J, f)
% Assure-toi que ce script définit bien les matrices A, B, C, D
run('E:\Mes-CD\Matlab-Projects\MoteurCC\params\init_params.m')

%% --- PARTIE 1 : CONCEPTION DU FILTRE DE KALMAN ---
% On suppose qu'on mesure uniquement la vitesse wm : y = [0 1]*x
C_kal = [0 1]; 

% Matrices de covariance du bruit
Q_kal = diag([0.01, 1]); % Bruit de processus (confiance dans le modèle)
R_kal = 10;              % Bruit de mesure (confiance dans le capteur)

% Résolution pour l'observateur (Dualité LQR)
[P_p, ~, L_trans] = care(A', C_kal', Q_kal, R_kal);
L_kal = L_trans';

%% --- PARTIE 2 : CONCEPTION DU RÉGULATEUR LQR ---
% On veut minimiser l'erreur sur le courant et la vitesse
% x = [courant_i ; vitesse_wm]
Q_lqr = diag([0.1, 10]); % On donne plus de poids (10) à la précision de vitesse
R_lqr = 0.01;            % Coût de l'énergie (plus petit = réponse plus rapide)

% Calcul du gain de retour d'état
K_lqr = lqr(A, B, Q_lqr, R_lqr);

%% --- AFFICHAGE DES RÉSULTATS ---
fprintf('\n==========================================\n');
fprintf('    SYNTHÈSE DE LA COMMANDE LQG (MOTEUR CC)   \n');
fprintf('==========================================\n');

fprintf('1. GAIN DE L''OBSERVATEUR (L_kal) :\n');
disp(L_kal);

fprintf('2. GAIN DE COMMANDE LQR (K_lqr) :\n');
disp(K_lqr);

% Vérification de la stabilité globale
poles_lqr = eig(A - B*K_lqr);
poles_obs = eig(A - L_kal*C_kal);

fprintf('3. STABILITÉ :\n');
fprintf('Pôles de commande (LQR) : %s\n', mat2str(round(poles_lqr, 2)));
fprintf('Pôles de l''observateur  : %s\n', mat2str(round(poles_obs, 2)));

if all(real(poles_lqr) < 0) && all(real(poles_obs) < 0)
    fprintf('\n✔ SYSTÈME GLOBALEMENT STABLE\n');
else
    fprintf('\n⚠ ATTENTION : Instabilité détectée\n');
end
fprintf('==========================================\n');
% Calcul du gain de pré-compensation pour que wm = consigne
C_vitesse = [0 1]; % On veut que la sortie 2 suive la consigne
Nbar = -1/(C_vitesse * inv(A - B(:,1)*K_lqr) * B(:,1));