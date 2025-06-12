function [C,S] = SolidTides(T,T2,T3,phiM,phiS,mu_Moon,mu_Sun,mu_Primary,r_ref,rS,rM,lS,lM,theta_g,x_pole,y_pole)
%{
© 2025 Yazan Chihabi
%}
    % Effect of Solid Earth Tides (anelastic Earth)
    % For dC21 and dS21
    % The coefficients we choose are in-phase(ip) amplitudes and out-of-phase amplitudes of the
    % corrections for frequency dependence, and multipliers of the Delaunay variables
    % Refer to Table 6.5a in IERS2010
    coeff0 = [...
	%  l   l'  F   D   Om  Amp(R) Amp(I)
       2,  0,  2,  0,  2,  -0.1,    0;    
       0,  0,  2,  2,  2,  -0.1,    0;    
       1,  0,  2,  0,  1,  -0.1,    0;    
       1,  0,  2,  0,  2,  -0.7,    0.1;  
      -1,  0,  2,  2,  2,  -0.1,    0;    
       0,  0,  2,  0,  1,  -1.3,    0.1;  
       0,  0,  2,  0,  2,  -6.8,    0.6;  
       0,  0,  0,  2,  0,   0.1,    0;    
       1,  0,  2, -2,  2,   0.1,    0;    
      -1,  0,  2,  0,  1,   0.1,    0;    
      -1,  0,  2,  0,  2,   0.4,    0;    
       1,  0,  0,  0,  0,   1.3,   -0.1;  
       1,  0,  0,  0,  1,   0.3,    0;    
      -1,  0,  0,  2,  0,   0.3,    0;    
      -1,  0,  0,  2,  1,   0.1,    0;    
       0,  1,  2, -2,  2,  -1.9,    0.1;  
       0,  0,  2, -2,  1,   0.5,    0;    
       0,  0,  2, -2,  2,  -43.4,   2.9;
       0, -1,  2, -2,  2,   0.6,    0;    
       0,  1,  0,  0,  0,   1.6,   -0.1;  
      -2,  0,  2,  0,  1,   0.1,    0;    
       0,  0,  0,  0, -2,   0.1,    0;    
       0,  0,  0,  0, -1,  -8.8,    0.5;  
       0,  0,  0,  0,  0,   470.9, -30.2; 
       0,  0,  0,  0,  1,   68.1,  -4.6;  
       0,  0,  0,  0,  2,  -1.6,    0.1;  
      -1,  0,  0,  1,  0,   0.1,    0;    
       0, -1,  0,  0, -1,  -0.1,    0;    
       0, -1,  0,  0,  0,  -20.6,  -0.3;  
       0,  1, -2,  2, -2,   0.3,    0;    
       0, -1,  0,  0,  1,  -0.3,    0;    
      -2,  0,  0,  2,  0,  -0.2,    0;    
      -2,  0,  0,  2,  1,  -0.1,    0;    
       0,  0, -2,  2, -2,  -5.0,    0.3;  
       0,  0, -2,  2, -1,   0.2,    0;    
       0, -1, -2,  2, -2,  -0.2,    0;    
       1,  0,  0, -2,  0,  -0.5,    0;    
       1,  0,  0, -2,  1,  -0.1,    0;    
      -1,  0,  0,  0, -1,   0.1,    0;    
      -1,  0,  0,  0,  0,  -2.1,    0.1;  
      -1,  0,  0,  0,  1,  -0.4,    0;    
       0,  0,  0, -2,  0,  -0.2,    0;    
      -2,  0,  0,  0,  0,  -0.1,    0;    
       0,  0, -2,  0, -2,  -0.6,    0;    
       0,  0, -2,  0, -1,  -0.4,    0;    
       0,  0, -2,  0,  0,  -0.1,    0;    
      -1,  0, -2,  0, -2,  -0.1,    0;    
      -1,  0, -2,  0, -1,  -0.1,    0;    
    ];
    % For dC20
    % The nominal value k20 for the zonal tides is taken as 0.30190
	% Refer to Table 6.5b in IERS2010
    coeff1 = [...
	% l   l'  F   D   Om  Amp(R)  Amp(I)
      0,  0,  0,  0,  1,  16.6,   -6.7;
      0,  0,  0,  0,  2,  -0.1,    0.1;
      0, -1,  0,  0,  0,  -1.2,    0.8;
      0,  0, -2,  2, -2,  -5.5,    4.3;
      0,  0, -2,  2, -1,   0.1,   -0.1;
      0, -1, -2,  2, -2,  -0.3,    0.2;
      1,  0,  0, -2,  0,  -0.3,    0.7;
     -1,  0,  0,  0, -1,   0.1,   -0.2;
     -1,  0,  0,  0,  0,  -1.2,    3.7;
     -1,  0,  0,  0,  1,   0.1,   -0.2;
      1,  0, -2,  0, -2,   0.1,   -0.2;
      0,  0,  0, -2,  0,   0.0,    0.6;
     -2,  0,  0,  0,  0,   0.0,    0.3;
      0,  0, -2,  0, -2,   0.6,    6.3;
      0,  0, -2,  0, -1,   0.2,    2.6;
      0,  0, -2,  0,  0,   0.0,    0.2;
      1,  0, -2, -2, -2,   0.1,    0.2;
     -1,  0, -2,  0, -2,   0.4,    1.1;
     -1,  0, -2,  0, -1,   0.2,    0.5;
      0,  0, -2, -2, -2,   0.1,    0.2;
     -2,  0, -2,  0, -2,   0.1,    0.1;
    ];
    % For dC22 and dS22
    % Refer to Table 6.5c in IERS2010
    coeff2 = [...
    % l  l' F  D  Om   Amp
      1, 0, 2, 0, 2,  -0.3;
      0, 0, 2, 0, 2,  -1.2;
    ];
    rev = 3600*360;
    % Mean arguments of luni-solar motion
    %
    %   l   mean anomaly of the Moon
    %   l'  mean anomaly of the Sun
    %   F   mean argument of latitude
    %   D   mean longitude elongation of the Moon from the Sun
    %   Om  mean longitude of the ascending node of the Moon
    l  = mod (  485866.733 + (1325.0*rev +  715922.633)*T...
                              + 31.310*T2 + 0.064*T3, rev );
    lp = mod ( 1287099.804 + (  99.0*rev + 1292581.224)*T...
                              -  0.577*T2 - 0.012*T3, rev );
    F  = mod (  335778.877 + (1342.0*rev +  295263.137)*T...
                              - 13.257*T2 + 0.011*T3, rev );
    D  = mod ( 1072261.307 + (1236.0*rev + 1105601.328)*T...
                              -  6.891*T2 + 0.019*T3, rev );
    Om = mod (  450160.280 - (   5.0*rev +  482890.539)*T...
                              +  7.455*T2 + 0.008*T3, rev );
    
    % STEP1 CORRECTIONS
    [lgM, ~] = dynamics.Legendre(4,4,phiM);
    [lgS, ~] = dynamics.Legendre(4,4,phiS);
    dCnm20 = (0.30190/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,1) );
    dCnm21 = (0.29830/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*cos(lS) )...
		   +(-0.00144/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*(sin(lM))...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*(sin(lS)) );
    dSnm21 = (0.00144/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*(cos(lM))...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*(cos(lS)) )...
		   + (0.29830/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*sin(lS) );
    dCnm22 = (0.30102/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*cos(2*lS) )...
		   +(-0.00130/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*(sin(2*lM))...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*(sin(2*lS)) );
    dSnm22 = (0.00130/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*(cos(2*lM))...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*(cos(2*lS)) )...
		   + (0.30102/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*sin(2*lS) );
    dCnm30 = (0.093/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,1) );
    dCnm31 = (0.093/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,2)*cos(lS) );
    dSnm31 = (0.093/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,2)*sin(lS) );
    dCnm32 = (0.093/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,3)*cos(2*lS) );
    dSnm32 = (0.093/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,3)*sin(2*lS) );
    dCnm33 = (0.094/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,4)*cos(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,4)*cos(3*lS) );
    dSnm33 = (0.094/7)*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,4)*sin(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,4)*sin(3*lS) );
    dCnm40 = (-0.00089/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(5,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(5,1) );
    dCnm41 = (-0.00080/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(5,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(5,2)*cos(lS) );
    dSnm41 = (-0.00080/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(5,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(5,2)*sin(lS) );
    dCnm42 = (-0.00057/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(5,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(5,3)*cos(2*lS) );
    dSnm42 = (-0.00057/5)*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(5,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(5,3)*sin(2*lS) );
    
    % STEP2 CORRECTIONS
    dC20 = 0;
    for i=1:21
        theta_f = -coeff1(i,1:5)*[l lp F D Om]';
        dC20 = dC20 + 1e-12*(coeff1(i,6)*cos(theta_f)-coeff1(i,7)*sin(theta_f));
    end
    dCnm20 = dCnm20 + dC20;
    
    
	
    dC21 = 0;
    dS21 = 0;
    for i=1:48
        theta_f = (theta_g+pi)-coeff0(i,1:5)*[l lp F D Om]';
        dC21 = dC21 + 1e-12*(coeff0(i,6)*sin(theta_f)+coeff0(i,7)*cos(theta_f));
        dS21 = dS21 + 1e-12*(coeff0(i,6)*cos(theta_f)-coeff0(i,7)*sin(theta_f));
    end
    dCnm21 = dCnm21 + dC21;
    dSnm21 = dSnm21 + dS21;
    
    dC22 = 0;
    dS22 = 0;
    for i=1:2
        theta_f = 2*(theta_g+pi)-coeff2(i,1:5)*[l lp F D Om]';
        dC22 = dC22 + 1e-12*coeff2(i,6)*sin(theta_f);
        dS22 = dS22 + 1e-12*coeff2(i,6)*cos(theta_f);
    end
    dCnm22 = dCnm22 + dC22;
    dSnm22 = dSnm22 + dS22;
    
    % Treatment of the Permanent Tide (anelastic Earth)
    dC20 = 4.4228e-8*(-0.31460)*0.30190;
    dCnm20 = dCnm20 - dC20;
    
    % Effect of Solid Earth Pole Tide (anelastic Earth)
    dC21 = -1.348e-9*(x_pole+0.0112*y_pole);
    dS21 = 1.348e-9*(y_pole-0.0112*x_pole);
    dCnm21 = dCnm21 + dC21;
    dSnm21 = dSnm21 + dS21;
    
    C = zeros(5,4);
    S = zeros(5,4);
    
    C(3,1) = dCnm20;
    C(3,2) = dCnm21;
    C(3,3) = dCnm22;
    S(3,2) = dSnm21;
    S(3,3) = dSnm22;
    
    C(4,1) = dCnm30;
    C(4,2) = dCnm31;
    C(4,3) = dCnm32;
    C(4,4) = dCnm33;
    S(4,2) = dSnm31;
    S(4,3) = dSnm32;
    S(4,4) = dSnm33;
    
    C(5,1) = dCnm40;
    C(5,2) = dCnm41;
    C(5,3) = dCnm42;
    S(5,2) = dSnm41;
    S(5,3) = dSnm42;   
end
