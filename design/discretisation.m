% =========================================================
%  discretisation.m
% =========================================================

%% Période d'échantillonnage
Te = 1e-3;    % 1 ms

%% Discrétisation ZOH
sys_c = ss(A, B, C, 0);
sys_d = c2d(sys_c, Te, 'zoh');

Ad = sys_d.A;
Bd = sys_d.B;
Cd = sys_d.C;

fprintf('Ad =\n'); disp(Ad)
fprintf('Bd =\n'); disp(Bd)

%% Vérification stabilité discrète
poles_discrets = eig(Ad);
fprintf('Pôles discrets :\n'); disp(poles_discrets)
fprintf('|poles| < 1 ? %d %d\n', abs(poles_discrets(1))<1, abs(poles_discrets(2))<1)