function phi = STM(states,mu,dt)
% EKF_RADAR State Transition Matrix (Two-Body)
% Copyright Yazan Chihabi 2024
states_target = states(1:6);
states_chaser = states(7:12);

A_target = Navigation.EKF_RADAR.Amatrix(states_target,mu);
A_chaser = Navigation.EKF_RADAR.Amatrix(states_chaser,mu);

A = zeros(12,12);

A(1:6,1:6) = A_target;
A(7:12,7:12) = A_chaser;

phi = eye(12,12);
phi = (A*dt)*(((A*dt)/2)*(((A*dt)/3)*((A*dt)/4 + phi)+phi)+phi)+phi;

end