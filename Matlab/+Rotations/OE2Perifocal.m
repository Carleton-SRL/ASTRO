function C_IP = OE2Perifocal(oe)
%{
© 2025 Yazan Chihabi
%}
inc = oe(3);
w = oe(4);
RAAN = oe(5);

co = cos(RAAN);
cw = cos(w);
ci = cos(inc);
so = sin(RAAN);
sw = sin(w);
si = sin(inc);

C_IP = [ co*cw - so*ci*sw , -co*sw - so*ci*cw ,  so*si ; 
         so*cw + co*ci*sw , -so*sw + co*ci*cw , -co*si ; 
         si*sw            ,  si*cw            ,  ci   ];
end

