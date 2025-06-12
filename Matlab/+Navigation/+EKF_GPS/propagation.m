function [ekf_priori] = propagation(ekf_pre, u, dt, Q, mu)
% EKF_GPS propagation phase
% Copyright Yazan Chihabi 2024
states_pre = ekf_pre(1:6);
n = length(states_pre);
P_pre = zeros(n,n);
for i = 1:n
    P_pre(:,i) = ekf_pre(i*n+1:(i+1)*n);
end

states_priori = Navigation.EKF_RADAR_Reduced.propagator(dt, [0,dt], states_pre, u, mu);
states_priori = states_priori(:,end);


phi = Navigation.EKF_RADAR_Reduced.STM(states_pre,mu,dt);
P_priori = phi*P_pre*phi' + Q;

ekf_priori = [states_priori;P_priori(:)];
end