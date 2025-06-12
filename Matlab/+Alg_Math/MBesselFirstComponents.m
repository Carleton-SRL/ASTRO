function B0 = MBesselFirstComponents(z,nu,trunc)

% Finds the components of the modified Bessel functions of the first kind
%{
© 2025 Yazan Chihabi
%}
% Refer to Chihabi, Y., and Ulrich, S., “Analytical Spacecraft Formation
% Dynamics in Eccentric Orbits with Gravitational, Drag and Third body
% Perturbations,” 29th AAS/AIAA Space Flight Mechanics Meeting, Ka’anapali,
% HI, 13-17 Jan, 2019.   

B0 = 0;
for k = 0:trunc
    
    B0 = B0 + (((z^2)/4)^k)/(Alg_Math.factorialm(k)*Alg_Math.factorialm(k+nu));
    
end
B0 = B0*(((z)/2)^nu);

end