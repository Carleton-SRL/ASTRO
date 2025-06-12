function a = Drag(dens, r, v, Area, mass, CD, Omega)
%--------------------------------------------------------------------------
%
% Drag: Computes the acceleration due to the atmospheric drag 
% 
% Inputs:
%   dens        Atmospheric Density [kg/m^3]
%   r           Satellite position vector in the inertial system [km]
%   v           Satellite velocity vector in the inertial system [km/s]
%   Area        Cross-section [m^2]
%   mass        Spacecraft mass [kg]
%   CD          Drag coefficient
%   Omega       Angular velocity of the Earth
%
% Output:
%   a           Acceleration (a=d^2r/dt^2) [km/s^2]
%
% 
%--------------------------------------------------------------------------
%{
© 2025 Yazan Chihabi
%}
% Earth angular velocity vector [rad/s]
omega = [0.0, 0.0, Omega]';

  
% Velocity relative to the Earth's atmosphere
v_rel = v - skew_matrix(omega)*r;
v_abs = sqrt(v_rel(1)^2 + v_rel(2)^2 + v_rel(3)^2);

% Acceleration
a= -0.5*CD*(Area/mass)*dens*v_abs*v_rel.*1000;
end
