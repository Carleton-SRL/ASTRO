function [tano,E] = M2tano(M,e,iterations)
%{
© 2025 Yazan Chihabi
%}
E = dynamics.eccentricanomaly(M,e,iterations);
omecosE         = 1.0-e*cos(E);
sintano         = sqrt(1-e^2)*sin(E)/omecosE;
costano         = (cos(E)-e)/omecosE;
tano    = atan2(sintano, costano);
tano    = mod(tano, 2*pi);

end