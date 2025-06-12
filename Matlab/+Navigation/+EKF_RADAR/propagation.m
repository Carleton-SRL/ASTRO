function [ekf_priori] = propagation(ekf_pre, u, dt, Q, mu)
% EKF_RADAR propagation phase
% Copyright Yazan Chihabi 2024
states_target = ekf_pre(1:6);
states_chaser = ekf_pre(7:12);
states_pre = [states_target;states_chaser];
n = length(states_pre);
P_pre = zeros(n,n);
for i = 1:n
    P_pre(:,i) = ekf_pre(i*n+1:(i+1)*n);
end

states_priori_target = Navigation.EKF_RADAR.propagator(dt, [0,dt], states_target, [0;0;0], mu); % Target
states_priori_target = states_priori_target(:,end);
states_priori_chaser = Navigation.EKF_RADAR.propagator(dt, [0,dt], states_chaser, u, mu); % Chaser
states_priori_chaser = states_priori_chaser(:,end);

states_priori = [states_priori_target;states_priori_chaser];

phi = Navigation.EKF_RADAR.STM(states_pre,mu,dt);
P_priori = phi*P_pre*phi' + Q;

ekf_priori = [states_priori;P_priori(:)];
end