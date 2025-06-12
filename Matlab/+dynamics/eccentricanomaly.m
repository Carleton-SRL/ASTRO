function E = eccentricanomaly(M0,e,iterations)
%{
© 2025 Yazan Chihabi
%}
% Approximates the eccentric anomaly of a spacecraft's orbit
E = M0;
M = M0;
for j = 1:iterations
    E = M +e*sin(E);
end

end