function [q] = rotm2quat(r )
%% Converts rotation matrix to quaternion
% Inputs:
%   rotm = rotation matrix (3x3 matrix)
% Outputs:
%   q = quaternion (4x1 matrix)

%{
© 2025 Yazan Chihabi
%}

e = [0;0;0];
n = 0.5*sqrt(1+r(1,1)+r(2,2)+r(3,3));

e(1) = r(2,3)-r(3,2);
e(2) = r(3,1)-r(1,3);
e(3) = r(1,2)-r(2,1);

if n == 0
    e(1) = sqrt((1+r(1,1))/2);
    e(2) = sqrt((1+r(2,2))/2);
    e(3) = sqrt((1+r(3,3))/2);
else
    a = (1/(4*n));
    e = a*e;
end

q = [e(1);e(2);e(3);n];

q = Rotations.NormalizeQuaternion(q); % Normalize and ensure q(4) is positive

end

