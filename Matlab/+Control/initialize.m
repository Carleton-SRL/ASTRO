%{
© 2025 Yazan Chihabi
%}
%% Controller

% Attitude (Bong Wie)
Kp_Attitude = sign(initialAttitude_Chaser(4))*0.03; % proportional gain value -> still needs to be chosen/optimized 
Kd_Attitude = 0.08; % derivative gain value -> still needs to be chosen/optimized

% Position LQR Control Law
A_1 = zeros(3,3); A_2 = eye(3,3);
A_3 = zeros(3,3);
A_4 = zeros(3,3);

% The gains to tune are Qs and Rs
QLQR = diag([1 1 1 1000 1000 1000]);
RLQR = (10^5)*eye(3,3);

A_3(1,1) = 3*(n1^2);
A_3(3,3) = -(n1^2);
A_4(1,2) = 2*n1;
A_4(2,1) = - A_4(1,2);

A = [A_1 A_2; A_3 A_4];
B = [zeros(3,3); eye(3,3)];

% ra = a1*(1+e1);
% rp = a1*(1-e1);
% ApogeeTuned = 0;
% 
% if ApogeeTuned == 1
%     A(4:6,1:6) = [-mu/(rp^3)*eye(3,3),zeros(3,3)];
% else
%     A(4:6,1:6) = [-mu/(ra^3)*eye(3,3),zeros(3,3)];
% end

K_lqr = lqr(A,B,QLQR,RLQR);