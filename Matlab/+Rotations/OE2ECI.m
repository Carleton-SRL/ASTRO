function [r_I_ini,v_I_ini] = OE2ECI(oe,mu)
%{
© 2025 Yazan Chihabi
%}
a = oe(1);
e = oe(2);
tano = oe(6);

p = a*(1-e^2);
r = p/(1+e*cos(tano));

r_P_ini = [ r*cos(tano); r*sin(tano); 0 ];
v_P_ini = [ -sqrt(mu/p)*sin(tano); sqrt(mu/p)*(e+cos(tano)); 0 ];

C_IP = Rotations.OE2Perifocal(oe);

r_I_ini = C_IP * r_P_ini;
v_I_ini = C_IP * v_P_ini;

end