function C = Cz(angle)

% Principal rotation about the z-axis
% Yazan Chihabi, 2020

C = [cos(angle) sin(angle) 0;
    -sin(angle) cos(angle) 0;
    0 0 1];

end