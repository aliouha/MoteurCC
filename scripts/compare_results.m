% ── Simulation 1 : Boucle ouverte ──
sim('models/MCC_boucle_ouverte');
out1 = sim('models/MCC_boucle_ouverte');
t1  = out1.ia_out.Time;
ia1 = out1.ia_out.Data;
wm1 = out1.wm_out.Data;

% ── Simulation 2 : Retour d'état ──
sim('models/MCC_retour_etat');
out2 = sim('models/MCC_retour_etat');
t2  = out2.ia_out.Time;
ia2 = out2.ia_out.Data;
wm2 = out2.wm_out.Data;

% ── Simulation 3 : Luenberger ──
L = [150.8619 ; 161.0594];
sim('models/MCC_retour_etat_estime');
out3 = sim('models/MCC_retour_etat_estime');
t3  = out3.ia_out.Time;
ia3 = out3.ia_out.Data;
wm3 = out3.wm_out.Data;

% ── Simulation 4 : Kalman ──
L = L_kal;
sim('models/MCC_retour_etat_estime_Kal');
out4 = sim('models/MCC_retour_etat_estime_Kal');
t4  = out4.ia_out.Time;
ia4 = out4.ia_out.Data;
wm4 = out4.wm_out.Data;

% ── Figure comparaison ──
figure('Name','Comparaison 4 conceptions','NumberTitle','off');

subplot(2,1,1)
plot(t1,ia1,'k',t2,ia2,'b',t3,ia3,'r',t4,ia4,'g','LineWidth',1.5)
xlabel('Temps (s)'); ylabel('ia (A)')
title('Courant ia(t) — Comparaison')
legend('Boucle ouverte','Retour état','Luenberger','Kalman')
grid on

subplot(2,1,2)
plot(t1,wm1,'k',t2,wm2,'b',t3,wm3,'r',t4,wm4,'g','LineWidth',1.5)
xlabel('Temps (s)'); ylabel('ωm (rad/s)')
title('Vitesse ωm(t) — Comparaison')
legend('Boucle ouverte','Retour état','Luenberger','Kalman')
grid on

saveas(gcf,'E:\Mes-CD\Matlab-Projects\MoteurCC\results\comparaison_finale.png')
fprintf('✔ Comparaison terminée !\n')