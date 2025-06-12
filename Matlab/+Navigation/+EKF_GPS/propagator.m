function state_output = propagator(dt, t, states, AppliedAccel, mu)
% EKF Two-Body Runge-Kutta Propagator
% Copyright Yazan Chihabi 2024
n = length(t);
state_output = zeros(6,n);
state_output(:,1) = states;
for i = 2:n
    k1 = dynamics.TwoBody(0,states,AppliedAccel,mu);
    k2 = dynamics.TwoBody(0,states + (1/3)*k1*dt,AppliedAccel,mu);
    k3 = dynamics.TwoBody(0,states + (1/6)*k1*dt + (1/6)*k2*dt,AppliedAccel,mu);
    k4 = dynamics.TwoBody(0,states + (1/8)*k1*dt + (3/8)*k3*dt,AppliedAccel,mu);
    k5 = dynamics.TwoBody(0,states + (1/2)*k1*dt - (3/2)*k3*dt + 2*k4*dt,AppliedAccel,mu);
    
    % Calculate the propagated state vector
    state_output(:,i) = states + (1/6)*(k1 + 4*k4 + k5)*dt;

    states = state_output(:,i);
end

end