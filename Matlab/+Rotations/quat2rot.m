function C = quat2rot(q)
%{
© 2025 Yazan Chihabi
%}
%obtain rotation matrix given quaternions
epsilon = [q(1);q(2);q(3)];
eta = q(4);
C = (eta^2-epsilon'*epsilon)*eye(3) + 2*(epsilon*epsilon') - 2*eta*skew_matrix(epsilon);
end