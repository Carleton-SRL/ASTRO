function A = Amatrix(states,mu)
% System State-Space A matrix for Two body motion
% x_dot = Ax + Bu
% Copyright Yazan Chihabi 2024

rI = states(1:3);
r = sqrt(rI(1)^2 + rI(2)^2 + rI(3)^2);

A = zeros(6,6);

A(1:3,4:6) = eye(3,3);
A(4:6,1:3) = -mu/(r^3).*A(1:3,4:6);

end