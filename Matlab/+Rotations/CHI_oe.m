function C_HI = CHI_oe(oe)% Gurfil and Kholshevnikovs equations
%{
© 2025 Yazan Chihabi
%}
inc = oe(3);
    w = oe(4);
    RAAN = oe(5);
    tano = oe(6);
    
   
    

    co = cos(RAAN);
    cw = cos(w);
    ci = cos(inc);
    so = sin(RAAN);
    sw = sin(w);
    si = sin(inc);
    kl1 = co*cw - so*ci*sw;
    kl2 = -co*sw - so*ci*cw;
    kl3 = so*si;
    kl4 = so*cw + co*ci*sw;
    kl5 = -so*sw + co*ci*cw;
    kl6 = -co*si;
    kl7 = si*sw;
    kl8 = si*cw;
    kl9 = ci;
    C_IP = [ kl1 , kl2 ,  kl3 ; 
              kl4 , kl5 ,  kl6 ; 
              kl7 , kl8 ,  kl9  ];

    C_PI = C_IP';
    ct=cos(tano);
    st=sin(tano);
    C_HP = [  ct, st, 0  ; 
              -st, ct, 0  ; 
                0,  0, 1 ];


    C_HI = C_HP * C_PI;
end 