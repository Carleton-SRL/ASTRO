function rnpb = iauPnm06a(date1, date2, ConstantParameters)
%{
© 2025 Yazan Chihabi
%}

% Fukushima-Williams angles for frame bias and precession
[gamb, phib, psib, epsa] = time_variables.iauPfw06(date1, date2, ConstantParameters);

% Nutation components
[dp, de] = time_variables.iauNut06a(date1, date2, ConstantParameters);

% Equinox based nutation x precession x bias matrix
rnpb = time_variables.iauFw2m(gamb, phib, psib + dp, epsa + de);
end
