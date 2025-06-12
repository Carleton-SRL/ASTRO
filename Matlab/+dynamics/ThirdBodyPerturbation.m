function a = ThirdBodyPerturbation(r, s, mu)
%{
© 2025 Yazan Chihabi
%}
% Relative position vector of satellite w.r.t. point mass 
d = r - s;

% Acceleration 
a = -mu * ( d/(norm(d)^3) + s/(norm(s)^3) );
end
