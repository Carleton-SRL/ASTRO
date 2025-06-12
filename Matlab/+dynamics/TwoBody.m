function X  = TwoBody(t,states,u,mu)
%{
© 2025 Yazan Chihabi
%}

rI = states(1:3);
vI = states(4:6);
r = sqrt(rI(1)^2 + rI(2)^2 + rI(3)^2);
aI = -(mu/(r^3)).*rI + u;

% jerkI = -(mu/(r^3)).*vI + (1.5*mu*(2*rI'*vI)/(r^5)).*rI;

X = [vI;aI];

end