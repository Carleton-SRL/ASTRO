function [oe,tano] = ECI2oe(r,v,mu)

% computes orbital elements from position/velocity
%{
© 2025 Yazan Chihabi
%}


rmod = sqrt(r(1)^2 + r(2)^2 + r(3)^2);
vmod = sqrt(v(1)^2 + v(2)^2 + v(3)^2);

r_skew = skew_matrix(r);
v_skew = skew_matrix(v);

% semi major axis

en = (vmod^2)/2 - mu/rmod;

a = - mu/(2*en);

% eccentricity
h_vec = r_skew*v;

e_vec = (v_skew*h_vec)/mu - r/rmod;
e = sqrt(e_vec(1)^2 + e_vec(2)^2 + e_vec(3)^2);

%inclination

hmod = sqrt(h_vec(1)^2 + h_vec(2)^2 + h_vec(3)^2);

i = acos((h_vec'*[0; 0; 1])/hmod);

% RAAN

Iz_skew = skew_matrix([0;0;1]);
N_vec = Iz_skew*h_vec;
Nmod = sqrt(N_vec(1)^2 + N_vec(2)^2 + N_vec(3)^2);

RAAN = acos((N_vec'*[1;0;0])/Nmod);

RAAN = mod(RAAN,2*pi);

if (N_vec'*[0; 1; 0]) < 0 && RAAN<pi
    RAAN = 2*pi - RAAN;
end
% argument of perigee

w = acos((N_vec'*e_vec)/(Nmod*e));
w = mod(w,2*pi);
if (e_vec'*[0; 0; 1]) < 0  && w<pi
    w = 2*pi - w;
end
  
% Mean anomaly

u = acos((N_vec'*r)/(Nmod*rmod));
u = mod(u,2*pi);
if (r'*[0; 0; 1]) < 0 && u<pi
    u = 2*pi - u;
end

tano = u - w;
  
tano    = mod(tano, 2*pi);


E = 2*atan(sqrt((1-e)/(1+e))*tan(tano/2));
E       = mod(E, 2*pi);

M = E - e*sin(E);
M       = mod(M, 2*pi);


oe = [a; e; i ; w; RAAN; M];
end
