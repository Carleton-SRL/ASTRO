%{
© 2025 Yazan Chihabi
%}

% Arcseconds to radians
ConstantParameters.AS2R =4.848136811095359935899141e-6;

% Pi 
ConstantParameters.DPI =3.141592653589793238462643;

% 2Pi 
ConstantParameters.D2PI =6.283185307179586476925287;

% Degrees to radians 
ConstantParameters.DD2R =1.745329251994329576923691e-2;

% Radians to arcseconds 
ConstantParameters.DR2AS =206264.8062470963551564734;

% Arcseconds to radians 
ConstantParameters.DAS2R =4.848136811095359935899141e-6;

% Seconds of time to radians 
ConstantParameters.DS2R =7.272205216643039903848712e-5;

% Arcseconds in a full circle 
ConstantParameters.TURNAS =1296000.0;

% Milliarcseconds to radians 
ConstantParameters.DMAS2R =ConstantParameters.DAS2R / 1e3;

% Length of tropical year B1900 (days) 
ConstantParameters.DTY =365.242198781;

% Seconds per day. 
ConstantParameters.DAYSEC =86400.0;

% Days per Julian year 
ConstantParameters.DJY =365.25;

% Days per Julian century 
ConstantParameters.DJC =36525.0;

% Days per Julian millennium 
ConstantParameters.DJM =365250.0;

% Reference epoch (J2000.0), Julian Date 
ConstantParameters.DJ00 =2451545.0;

% Julian Date of Modified Julian Date zero 
ConstantParameters.DJM0 =2400000.5;

% Reference epoch (J2000.0), Modified Julian Date 
ConstantParameters.DJM00 =51544.5;

% 1977 Jan 1.0 as MJD 
ConstantParameters.DJM77 =43144.0;

% TT minus TAI (s) 
ConstantParameters.TTMTAI =32.184;

% Astronomical unit [km]; DE405;
ConstantParameters.DAU =149597870.691000015;

% Speed of light (km/s)
ConstantParameters.CMPS = 299792.4580;

% Light time for 1 au (s)
ConstantParameters.AULT = 499.004782;

% Speed of light (AU per day) 
ConstantParameters.DC =ConstantParameters.DAYSEC / 499.004782;

% L_G = 1 - d(TT)/d(TCG) 
ConstantParameters.ELG =6.969290134e-10;

% L_B = 1 - d(TDB)/d(TCB), and TDB (s) at TAI 1977/1/1.0 
ConstantParameters.ELB =1.550519768e-8;
ConstantParameters.TDB0 =-6.55e-5;

% Schwarzschild radius of the Sun (au)
% = 2 * 1.32712440041e20 / (2.99792458e8)^2 / 1.49597870700e11
ConstantParameters.SRS = 1.97412574336e-8;

