%{
© 2025 Yazan Chihabi
%}

% [r2_E_ini, v2_E_ini, a2_E_ini] = eci2ecef(invjday(JD0), r2_I_ini, ...
%     v2_I_ini, X_ini(4:6),'pm',[x_pole,y_pole],'dCIP',[dx_pole,dy_pole], ...
%     'lod',LOD,'dAT',TAI_UTC,'dUT1',-UT1_UTC); % Convert  to ECEF

% 
% % Polar motion matrix (TIRS->ITRS, IERS 2003)
% Pi = iauPom00(x_pole, y_pole, iauSp00(DJMJD0, TT, ConstantParameters));
% % Form bias-precession-nutation matrix
% NPB = iauPnm06a(DJMJD0, TT, ConstantParameters);
% 
% % Form Earth rotation matrix
% gast = iauGst06(DJMJD0, UT1, DJMJD0, TT, NPB, ConstantParameters);
% Theta  = iauRz(gast, eye(3));
% % ICRS to ITRS transformation
% C_EI = Pi*Theta*NPB;
% % C_EI = ECI2ECEF_Rot(thetaGMT(1));
% % r2_E_ini = C_EI*r2_I_ini;
% % v2_E_ini = C_EI*v2_I_ini;
% % a2_E_ini = C_EI*a2_I_ini;
% % r2_E_ini = C_EI*r2_I_ini;
% % v2_E_ini = C_EI*v2_I_ini - wEx*r2_E_ini;
% % a2_E_ini = C_EI*a2_I_ini - wEx*v2_E_ini;
% jerk2_E_ini = C_EI*jerk2_I_ini - wEx*a2_E_ini;
% 
% % v2_E_ini = C_EI*v2_I_ini;
% % a2_E_ini = C_EI*a2_I_ini;
% % jerk2_E_ini = C_EI*jerk2_I_ini;

[r2_E_ini,v2_E_ini,a2_E_ini,~] = Rotations.ECI2ECEF(MJD_UTC0, [r2_I_ini;v2_I_ini;X_ini(4:6)], ConstantParameters, eopdata);
lla_ini = ecef2lla(r2_E_ini');