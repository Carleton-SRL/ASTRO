function C_HI  =  CHI(states)
r_I = states(1:3);
v_I = states(4:6);
% ---------------------------------------------------------------
% CHI
% ---------------------------------------------------------------
% Description:
% Compute the rotation matrix from ECI to Hill's, i.e. C_HI
% ---------------------------------------------------------------
% Inputs:
% r_I => components of r in ECI (3 x 1 matrix)
% v_I => components of v in ECI (3 x 1 matrix)
% ---------------------------------------------------------------
% Outputs:
% C_HI => rotation matrix from ECI to Hill's (3 x 3 matrix)
% ---------------------------------------------------------------
% Parameters:
% None
% ---------------------------------------------------------------
% Copyright:
% Steve Ulrich, 2015 
% ---------------------------------------------------------------

Hx = zeros(3,1);
Hy = zeros(3,1);
Hz = zeros(3,1);
C_HI = zeros(3);

% Compute orbital radius and orbital speed
rmod = sqrt(r_I(1)*r_I(1) + r_I(2)*r_I(2) + r_I(3)*r_I(3));
vmod = sqrt(v_I(1)*v_I(1) + v_I(2)*v_I(2) + v_I(3)*v_I(3));

% Compute Hx unit vector, i.e., first row of C_HI
Hx(1) = r_I(1)/rmod;
Hx(2) = r_I(2)/rmod;
Hx(3) = r_I(3)/rmod;

% Compute Hz unit vector, i.e., third row of C_HI
Hz(1) = (-r_I(3)*v_I(2)+r_I(2)*v_I(3));
Hz(2) = ( r_I(3)*v_I(1)-r_I(1)*v_I(3));
Hz(3) = (-r_I(2)*v_I(1)+r_I(1)*v_I(2));

Hzmod = sqrt(Hz(1)^2+Hz(2)^2+Hz(3)^2);

Hz(1) = Hz(1)/Hzmod;
Hz(2) = Hz(2)/Hzmod;
Hz(3) = Hz(3)/Hzmod;

% Compute Hy unit vector, i.e., second row of C_HI
Hy(1) = (-Hz(3)*Hx(2)+Hz(2)*Hx(3));
Hy(2) = ( Hz(3)*Hx(1)-Hz(1)*Hx(3));
Hy(3) = (-Hz(2)*Hx(1)+Hz(1)*Hx(2));

C_HI = [Hx(1), Hx(2), Hx(3); Hy(1), Hy(2), Hy(3); Hz(1), Hz(2), Hz(3)];
end
