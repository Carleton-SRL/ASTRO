function C = Cx(angle)

% Principal rotation about the x-axis
% Yazan Chihabi, 2020

C = [1 0 0;
    0 cos(angle) sin(angle);
    0 -sin(angle) cos(angle)];

end