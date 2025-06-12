function state_output = propagator(dt, t, states, AppliedTorque, w_rw, ...
    wdot_rw, inertiaMatrix, inertiaMatrix_inv)
%{
© 2025 Yazan Chihabi
%}
n = length(t);
state_output = zeros(7,n);
state_output(:,1) = states;
for i = 2:n
    k1 = dynamics.Attitude.simulator(0,states,AppliedTorque, ...
            w_rw, wdot_rw, inertiaMatrix, inertiaMatrix_inv);
    k2 = dynamics.Attitude.simulator(0,states + (1/3)*k1*dt,AppliedTorque, ...
            w_rw, wdot_rw, inertiaMatrix, inertiaMatrix_inv);
    k3 = dynamics.Attitude.simulator(0,states + (1/6)*k1*dt + (1/6)*k2*dt,AppliedTorque, ...
            w_rw, wdot_rw, inertiaMatrix, inertiaMatrix_inv);
    k4 = dynamics.Attitude.simulator(0,states + (1/8)*k1*dt + (3/8)*k3*dt,AppliedTorque, ...
            w_rw, wdot_rw, inertiaMatrix, inertiaMatrix_inv);
    k5 = dynamics.Attitude.simulator(0,states + (1/2)*k1*dt - (3/2)*k3*dt + 2*k4*dt,AppliedTorque, ...
            w_rw, wdot_rw, inertiaMatrix, inertiaMatrix_inv);
    
    % Calculate the propagated state vector
    state_output(:,i) = states + (1/6)*(k1 + 4*k4 + k5)*dt;

    states = state_output(:,i);
end

end