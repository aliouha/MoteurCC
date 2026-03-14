% =========================================================
%  run_boucle_ouverte.m
% =========================================================
cd('E:\Mes-CD\Matlab-Projects\MoteurCC')
addpath(genpath(pwd))

% Charger les paramètres
run('params/init_params.m')

% Lancer la simulation
sim('models/MCC_boucle_ouverte')

% Lancer la simulation
out = sim('models/MCC_boucle_ouverte');

% Récupération des données
t  = out.ia_out.Time;
ia = out.ia_out.Data;
wm = out.wm_out.Data;

% Tracer les résultats
figure('Name','Boucle Ouverte','NumberTitle','off');

subplot(2,1,1)
plot(t, ia, 'b', 'LineWidth', 1.5)
xlabel('Temps (s)'); ylabel('ia (A)')
title('Courant d''induit ia(t)')
grid on

subplot(2,1,2)
plot(t, wm, 'r', 'LineWidth', 1.5)
xlabel('Temps (s)'); ylabel('ωm (rad/s)')
title('Vitesse angulaire ωm(t)')
grid on

saveas(gcf, 'results/boucle_ouverte.png')
fprintf('✔ Simulation boucle ouverte terminée\n')