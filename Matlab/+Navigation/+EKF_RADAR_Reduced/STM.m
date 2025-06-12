function phi = STM(states,mu,dt)
% EKF_RADAR State Transition Matrix (Two-Body)
% Copyright Yazan Chihabi 2024

A = Navigation.EKF_RADAR.Amatrix(states,mu);


phi = eye(6,6);
phi = (A*dt)*(((A*dt)/2)*(((A*dt)/3)*((A*dt)/4 + phi)+phi)+phi)+phi;

end