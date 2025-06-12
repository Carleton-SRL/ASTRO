function q_dot = Kinematics(angularVelocity, q)
%{
© 2025 Yazan Chihabi
%}
%% Attitude Kinematics in terms of quaternions
% Inputs:
%   angularVelocity = Angular velocity of spacecraft (rads/sec) 
%   q = Current quaternions
% Outputs:
%   q_dot = Quaternion angular rate 

%Define omega
omega = [-skew_matrix(angularVelocity), angularVelocity; -angularVelocity', 0];
% Calculate q_dot
q_dot = (1/2)*omega*q;

end
