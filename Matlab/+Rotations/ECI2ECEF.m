function [r,v,a,LOD] = ECI2ECEF(MJD_UTC, Y0, ConstantParameters, eopdata)
%{
© 2025 Yazan Chihabi
%}
JD = MJD_UTC+2400000.5;
[x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = time_variables.IERS(eopdata,MJD_UTC,'l',ConstantParameters);
% [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = time_variables.timediff(UT1_UTC,TAI_UTC);
% MJD_UT1 = MJD_UTC + UT1_UTC/86400;
% MJD_TT = MJD_UTC + TT_UTC/86400;
% % Form bias-precession-nutation matrix
% NPB = time_variables.iauPnm06a(ConstantParameters.DJM0, MJD_TT,ConstantParameters);
% % Form Earth rotation matrix
% Theta = time_variables.iauRz( time_variables.iauGst06(ConstantParameters.DJM0, MJD_UT1, ConstantParameters.DJM0, MJD_TT, NPB,ConstantParameters),eye(3) );
% % Polar motion matrix (TIRS->ITRS, IERS 2003)
% Pi = time_variables.iauPom00(x_pole, y_pole, time_variables.iauSp00(ConstantParameters.DJM0, MJD_TT,ConstantParameters));
% % ICRS to ITRS transformation matrix and derivative
% S = zeros(3);
% S(1,2) = 1;
% S(2,1) = -1;              			 % Derivative of Earth rotation
% % Omega  = 7292115.8553e-11+4.3e-15*( (MJD_UTC-const.MJD_J2000)/36525 ); % [rad/s]
% Omega = ConstantParameters.omega_Earth-0.843994809*1e-9*LOD;  % IERS
% dTheta = Omega*S*Theta;           				 % matrix [1/s]
% U      = Pi*Theta*NPB;                			 % ICRS to ITRS transformation
% dU     = Pi*dTheta*NPB;               			 % Derivative [1/s]
% % Transformation from ICRS to WGS
% r = U*Y0(1:3);
% v = U*Y0(4:6) + dU*Y0(1:3);
% a = U*Y0(7:9) + dU*Y0(4:6);

[r,v,a] = eci2ecef(time_variables.invjday(JD), Y0(1:3), Y0(4:6), Y0(7:9), ...
    'pm',[x_pole,y_pole],'dCIP',[dx_pole,dy_pole], ...
    'lod',LOD,'dAT',TAI_UTC,'dUT1',-UT1_UTC);
end