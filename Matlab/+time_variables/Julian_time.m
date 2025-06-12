function [UT1,DJMJD0,DATE,TT,JD,MJD_UTC,r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, ...
 r_Neptune,r_Pluto,r_Moon,r_Sun,r_SunSSB,E,UT1_UTC,TT_UTC,x_pole,y_pole,NPB] = Julian_time(t, MJD_initial, centralbody, ConstantParameters, eopdata, PC)
%{
© 2025 Yazan Chihabi
%}

% Time and Constants
MJD_UTC = MJD_initial + t/86400;
[x_pole,y_pole,UT1_UTC,LOD,~,deps,dx_pole,dy_pole,TAI_UTC] = time_variables.IERS(eopdata,MJD_UTC,'l',ConstantParameters);
[UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = time_variables.timediff(UT1_UTC,TAI_UTC);

JD = MJD_UTC+2400000.5;
UTC_Time = time_variables.invjday(JD);
year = UTC_Time(1);
month = UTC_Time(2);
day = UTC_Time(3);
hour = UTC_Time(4);
minute = UTC_Time(5);
sec = UTC_Time(6); 
[DJMJD0, DATE] = time_variables.iauCal2jd(year, month, day);
TIME = (60*(60*hour + minute) + sec)/86400;
UTC = DATE + TIME;
TT = UTC + TT_UTC/86400;
TUT = TIME + UT1_UTC/86400;
UT1 = DATE + TUT;

% Polar motion matrix (TIRS->ITRS, IERS 2003)
Pi = time_variables.iauPom00(x_pole, y_pole, time_variables.iauSp00(DJMJD0, TT, ConstantParameters));
% Form bias-precession-nutation matrix
NPB = time_variables.iauPnm06a(DJMJD0, TT, ConstantParameters);

% Form Earth rotation matrix
gast = time_variables.iauGst06(DJMJD0, UT1, DJMJD0, TT, NPB, ConstantParameters);
Theta  = time_variables.iauRz(gast, eye(3));
% ICRS to ITRS transformation
E = Pi*Theta*NPB;

MJD_TDB = time_variables.Mjday_TDB(TT);
[r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, ...
 r_Neptune,r_Pluto,r_Moon,r_Sun,r_SunSSB,EMRAT1] = time_variables.JPL_Eph_DE436(MJD_TDB,PC);
if centralbody(1) == 1
    r_Earth = r_Earth-EMRAT1*r_Moon;
    r_Mercury = -r_Earth+r_Mercury;
    r_Venus = -r_Earth+r_Venus;
    r_Mars = -r_Earth+r_Mars;
    r_Jupiter = -r_Earth+r_Jupiter;
    r_Saturn = -r_Earth+r_Saturn;
    r_Uranus = -r_Earth+r_Uranus;
    r_Neptune = -r_Earth+r_Neptune;
    r_Pluto = -r_Earth+r_Pluto;
    r_Sun = -r_Earth+r_Sun;
    
    r_Earth = r_Earth./1000;
    r_Mercury = r_Mercury./1000;
    r_Venus = r_Venus./1000;
    r_Mars = r_Mars./1000;
    r_Jupiter = r_Jupiter./1000;
    r_Saturn = r_Saturn./1000;
    r_Uranus = r_Uranus./1000;
    r_Neptune = r_Neptune./1000;
    r_Pluto = r_Pluto./1000;
    r_SunSSB = r_SunSSB./1000;
    r_Sun = r_Sun./1000;
    r_Moon = r_Moon./1000;
elseif centralbody(1) == 2
    r_Earth = r_Earth-EMRAT1*r_Moon;
    r_Mercury = -r_Moon+r_Mercury;
    r_Venus = -r_Moon+r_Venus;
    r_Mars = -r_Moon+r_Mars;
    r_Jupiter = -r_Moon+r_Jupiter;
    r_Saturn = -r_Moon+r_Saturn;
    r_Uranus = -r_Moon+r_Uranus;
    r_Neptune = -r_Moon+r_Neptune;
    r_Pluto = -r_Moon+r_Pluto;
    r_Sun = -r_Moon+r_Sun;
    
    r_Earth = -r_Earth./1000;
    r_Mercury = r_Mercury./1000;
    r_Venus = r_Venus./1000;
    r_Mars = r_Mars./1000;
    r_Jupiter = r_Jupiter./1000;
    r_Saturn = r_Saturn./1000;
    r_Uranus = r_Uranus./1000;
    r_Neptune = r_Neptune./1000;
    r_Pluto = r_Pluto./1000;
    r_SunSSB = r_SunSSB./1000;
    r_Sun = r_Sun./1000;
    r_Moon = r_Moon./1000;

end

end
