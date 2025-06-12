function a = RelativisticPerturbation(r, v, r_Sun, v_Sun, mu_Primary, mu_Sun, c_light, J)
%--------------------------------------------------------------------------
%
% Calculates perturbing acceleration due to Relativistic Effects
% [1] Sofel, M., "Report of the working group Relativity for Celestial
% Mechanics and Astrometry," Proc. of IAU Colloquium 180, Johnston, K. J.,
% McCarthy, D. D., Luzum  B. J., and Kaplan, G. H. (eds.), U. S. Naval
% Observatory, Washington, D. C., 2000, pp. 283-292.
% [2] Sofel, M., Klioner, S., Petit, G., and Wolf, P., \The IAU2000
% resolutions for astrometry, celestial mechanics and metrology in the
% relativistic framework: explanatory supplement," The Astronomical
% Journal, 2003, pp. 2687-2706.  
%
% Inputs:
%   r           Satellite position vector
%   v           Satellite velocity vector
% 
% Output:
%   a    		Acceleration (a=d^2r/dt^2)
%
%--------------------------------------------------------------------------
%{
© 2025 Yazan Chihabi
%}

% Relative position vector of satellite w.r.t. point mass 
r_Sat = norm(r);
v_Sat = norm(v);
r_skew = skew_matrix(r);
v_skew = skew_matrix(v);

% Acceleration 
a = mu_Primary/(c_light^2*r_Sat^3)*((4*mu_Primary/r_Sat-v_Sat^2)*r+4*(r'*v)*v)...
    + 2*mu_Primary/(c_light^2*r_Sat^3)*(3/(r_Sat^2)*(r'*J)*(r_skew*v) + v_skew*J);
end
