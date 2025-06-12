function X = simulator(t,states,appliedTorque, w_rw, wdot_rw, ...
    inertiaMatrix, inertiaMatrix_inv)
%{
© 2025 Yazan Chihabi
%}
quaternion = states(1:4);
angularVelocity = states(5:7);

angularAcceleration = dynamics.Attitude.Dynamics(appliedTorque, w_rw, wdot_rw, angularVelocity, ...
    inertiaMatrix, inertiaMatrix_inv);

quaternion_dot = dynamics.Attitude.Kinematics(angularVelocity, quaternion);

X = [quaternion_dot;angularAcceleration];
end