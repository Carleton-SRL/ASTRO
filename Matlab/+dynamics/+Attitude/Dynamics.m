function angularAcceleration = Dynamics(appliedTorque, w_rw, wdot_rw, angularVelocity, ...
    inertiaMatrix, inertiaMatrix_inv)
%{
© 2025 Yazan Chihabi
%}
%% Euler's Equation of Motion
% Inputs:
%   innertiaMatrix = Inertia matrix
%   angularVelocity =  Angular velocity of spacecraft (rads/sec)
%   appliedTorque = All torque applied (control torque and pertubations)
% Outputs:
%   angularAcceleration = Spacecraft Angular acceleration 
RW_inertia_Chaser = 0;
J_w = [RW_inertia_Chaser,0,0;0,RW_inertia_Chaser,0;0,0,RW_inertia_Chaser];
w_b = angularVelocity;
T = appliedTorque;
w_b_skew = skew_matrix(w_b);

angularAcceleration = (inertiaMatrix_inv)*(T-(w_b_skew*(inertiaMatrix*w_b+J_w*w_rw))-J_w*wdot_rw);

end