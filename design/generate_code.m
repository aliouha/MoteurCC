% =========================================================
%  generate_code.m — Export paramètres pour C++
% =========================================================
run('E:\Mes-CD\Matlab-Projects\MoteurCC\params\init_params.m')
run('E:\Mes-CD\Matlab-Projects\MoteurCC\design\pole_placement.m')
run('E:\Mes-CD\Matlab-Projects\MoteurCC\design\kalman_design.m')
run('E:\Mes-CD\Matlab-Projects\MoteurCC\design\discretisation.m')

% Discrétisation du gain L Kalman
L_kal_d = L_kal;    % L reste le même en discret (approximation)

% Génération fichier params.h
fid = fopen('E:\Mes-CD\Matlab-Projects\MoteurCC\embedded\params.h', 'w');

fprintf(fid, '// =====================================================\n');
fprintf(fid, '// params.h — Paramètres MCC générés par MATLAB\n');
fprintf(fid, '// Moteur: Ra=%.2f Ohm, La=%.1fmH, J=%.2f Kg.m2\n', Ra, La*1e3, J);
fprintf(fid, '// =====================================================\n\n');
fprintf(fid, '#pragma once\n\n');

fprintf(fid, '// Periode echantillonnage\n');
fprintf(fid, '#define TE         %.4ff\n\n', Te);

fprintf(fid, '// Limites moteur\n');
fprintf(fid, '#define VA_MAX     %.1ff\n', Va);
fprintf(fid, '#define IA_MAX     50.0f\n');
fprintf(fid, '#define WM_MAX     %.1ff\n', Va/Kphi);
fprintf(fid, '#define VBUS       150.0f\n\n');

fprintf(fid, '// Modele discret Ad\n');
fprintf(fid, '#define AD_00      %.6ff\n', Ad(1,1));
fprintf(fid, '#define AD_01      %.6ff\n', Ad(1,2));
fprintf(fid, '#define AD_10      %.6ff\n', Ad(2,1));
fprintf(fid, '#define AD_11      %.6ff\n\n', Ad(2,2));

fprintf(fid, '// Modele discret Bd\n');
fprintf(fid, '#define BD_0       %.6ff\n', Bd(1));
fprintf(fid, '#define BD_1       %.6ff\n\n', Bd(2));

fprintf(fid, '// Gain retour etat K\n');
fprintf(fid, '#define K_0        %.6ff\n', K(1));
fprintf(fid, '#define K_1        %.6ff\n\n', K(2));

fprintf(fid, '// Gain pre-compensation\n');
fprintf(fid, '#define NR         %.6ff\n\n', Nr);

fprintf(fid, '// Gain Kalman L\n');
fprintf(fid, '#define L_0        %.6ff\n', L_kal(1));
fprintf(fid, '#define L_1        %.6ff\n\n', L_kal(2));

fprintf(fid, '// Reference vitesse\n');
fprintf(fid, '#define WM_REF     190.0f\n');

fclose(fid);
fprintf('✔ params.h généré !\n')