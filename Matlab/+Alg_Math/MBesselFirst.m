function B = MBesselFirst(a,c,trunc)
% Finds the modified Bessel functions of the first kind
%{
© 2025 Yazan Chihabi
%}
% Refer to Chihabi, Y., and Ulrich, S., “Analytical Spacecraft Formation
% Dynamics in Eccentric Orbits with Gravitational, Drag and Third body
% Perturbations,” 29th AAS/AIAA Space Flight Mechanics Meeting, Ka’anapali,
% HI, 13-17 Jan, 2019.  
B = zeros(1,length(a));
for j = 1:length(a)
    B(j) = Alg_Math.MBesselFirstComponents(c,a(j),trunc);
end

end