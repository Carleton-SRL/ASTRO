function C = Cy(angle)

% Principal rotation about the y-axis
% Yazan Chihabi, 2020

C = [cos(angle) 0 -sin(angle);
    0 1 0;
    sin(angle) 0 cos(angle)];

end