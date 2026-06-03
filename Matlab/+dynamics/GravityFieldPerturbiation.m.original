function a = GravityFieldPerturbiation(r,d,E,nmax,nmin,C,S,mu_Primary,r_ref)
%{
© 2025 Yazan Chihabi
%}
% ECEF position 
r_bf = E * r;

% Auxiliary quantities
                  % distance
latgc = asin(r_bf(3)/d);
lon = atan2(r_bf(2),r_bf(1));

[pnm, dpnm] = dynamics.Legendre(nmax,nmin,latgc);

dUdr = 0;
dUdlatgc = 0;
dUdlon = 0;
q3 = 0; q2 = q3; q1 = q2;
for n=0:nmax
    b1 = (-mu_Primary/d^2)*(r_ref/d)^n*(n+1);
    b2 =  (mu_Primary/d)*(r_ref/d)^n;
    b3 =  (mu_Primary/d)*(r_ref/d)^n;
    for m=0:nmin
        q1 = q1 + pnm(n+1,m+1)*(C(n+1,m+1)*cos(m*lon)+S(n+1,m+1)*sin(m*lon));
        q2 = q2 + dpnm(n+1,m+1)*(C(n+1,m+1)*cos(m*lon)+S(n+1,m+1)*sin(m*lon));
        q3 = q3 + m*pnm(n+1,m+1)*(S(n+1,m+1)*cos(m*lon)-C(n+1,m+1)*sin(m*lon));
    end
    dUdr     = dUdr     + q1*b1;
    dUdlatgc = dUdlatgc + q2*b2;
    dUdlon   = dUdlon   + q3*b3;
    q3 = 0; q2 = q3; q1 = q2;
end

% Body-fixed acceleration
r2xy = r_bf(1)^2+r_bf(2)^2;

ax = (1/d*dUdr-r_bf(3)/(d^2*sqrt(r2xy))*dUdlatgc)*r_bf(1)-(1/r2xy*dUdlon)*r_bf(2);
ay = (1/d*dUdr-r_bf(3)/(d^2*sqrt(r2xy))*dUdlatgc)*r_bf(2)+(1/r2xy*dUdlon)*r_bf(1);
az =  1/d*dUdr*r_bf(3)+sqrt(r2xy)/d^2*dUdlatgc;

a_bf = [ax ay az]';

% Inertial acceleration 
a = E'*a_bf;
end
