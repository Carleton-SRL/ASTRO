function [C,S] = OceanTides(phiM,phiS,mu_Moon,mu_Sun,mu_Primary,r_ref,rS,rM,lS,lM)
%{
© 2025 Yazan Chihabi
%}
    % Ocean Tides
    [lgM, ~] = dynamics.Legendre(6,6,phiM);
    [lgS, ~] = dynamics.Legendre(6,6,phiS);
    
    dCnm20 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.3075)/5*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,1) );
    dCnm21 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.3075)/5*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*cos(lS) );
    dSnm21 = -0.3075/5*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,2)*sin(lS) );
    dCnm22 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.3075)/5*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*cos(2*lS) );
    dSnm22 = -0.3075/5*( (mu_Moon/mu_Primary)*((r_ref/rM)^3)*lgM(3,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^3)*lgS(3,3)*sin(2*lS) );
    dCnm30 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.195)/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,1) );
    dCnm31 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.195)/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,2)*cos(lS) );
    dSnm31 = -0.195/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,2)*sin(lS) );
    dCnm32 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.195)/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,3)*cos(2*lS) );
    dSnm32 = -0.195/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,3)*sin(2*lS) );
    dCnm33 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.195)/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,4)*cos(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,4)*cos(3*lS) );
    dSnm33 = -0.195/7*( (mu_Moon/mu_Primary)*((r_ref/rM)^4)*lgM(4,4)*sin(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^4)*lgS(4,4)*sin(3*lS) );
    dCnm40 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.132)/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,1) );
    dCnm41 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.132)/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,2)*cos(lS) );
    dSnm41 = -0.132/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,2)*sin(lS) );
    dCnm42 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.132)/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,3)*cos(2*lS) );
    dSnm42 = -0.132/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,3)*sin(2*lS) );
    dCnm43 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.132)/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,4)*cos(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,4)*cos(3*lS) );
    dSnm43 = -0.132/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,4)*sin(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,4)*sin(3*lS) );
    dCnm44 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.132)/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,5)*cos(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,5)*cos(4*lS) );
    dSnm44 = -0.132/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^5)*lgM(5,5)*sin(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^5)*lgS(5,5)*sin(4*lS) );
    dCnm50 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,1) );
    dCnm51 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,2)*cos(lS) );
    dSnm51 = -0.1032/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,2)*sin(lS) );
    dCnm52 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,3)*cos(2*lS) );
    dSnm52 = -0.1032/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,3)*sin(2*lS) );
    dCnm53 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,4)*cos(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,4)*cos(3*lS) );
    dSnm53 = -0.1032/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,4)*sin(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,4)*sin(3*lS) );
    dCnm54 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,5)*cos(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,5)*cos(4*lS) );
    dSnm54 = -0.1032/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,5)*sin(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,5)*sin(4*lS) );
    dCnm55 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.1032)/11*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,6)*cos(5*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,6)*cos(5*lS) );
    dSnm55 = -0.1032/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^6)*lgM(6,6)*sin(5*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^6)*lgS(6,6)*sin(5*lS) );
    dCnm60 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,1)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,1) );
    dCnm61 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,2)*cos(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,2)*cos(lS) );
    dSnm61 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,2)*sin(lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,2)*sin(lS) );
    dCnm62 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,3)*cos(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,3)*cos(2*lS) );
    dSnm62 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,3)*sin(2*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,3)*sin(2*lS) );
    dCnm63 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,4)*cos(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,4)*cos(3*lS) );
    dSnm63 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,4)*sin(3*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,4)*sin(3*lS) );
    dCnm64 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,5)*cos(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,5)*cos(4*lS) );
    dSnm64 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,5)*sin(4*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,5)*sin(4*lS) );
    dCnm65 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,6)*cos(5*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,6)*cos(5*lS) );
    dSnm65 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,6)*sin(5*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,6)*sin(5*lS) );
    dCnm66 = 4*pi*r_ref^2*1025/(5.9722e24)*(1-0.0892)/13*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,7)*cos(6*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,7)*cos(6*lS) );
    dSnm66 = -0.0892/9*( (mu_Moon/mu_Primary)*((r_ref/rM)^7)*lgM(7,7)*sin(6*lM)...
           + (mu_Sun/mu_Primary)*((r_ref/rS)^7)*lgS(7,7)*sin(6*lS) );
    
    C = zeros(7,7);
    S = zeros(7,7);
       
       
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
    C(5,4) = dCnm43;
    C(5,5) = dCnm44;
    S(5,2) = dSnm41;
    S(5,3) = dSnm42;
    S(5,4) = dSnm43;
    S(5,5) = dSnm44;
    
    C(6,1) = dCnm50;
    C(6,2) = dCnm51;
    C(6,3) = dCnm52;
    C(6,4) = dCnm53;
    C(6,5) = dCnm54;
    C(6,6) = dCnm55;
    S(6,2) = dSnm51;
    S(6,3) = dSnm52;
    S(6,4) = dSnm53;
    S(6,5) = dSnm54;
    S(6,6) = dSnm55;
    
    C(7,1) = dCnm60;
    C(7,2) = dCnm61;
    C(7,3) = dCnm62;
    C(7,4) = dCnm63;
    C(7,5) = dCnm64;
    C(7,6) = dCnm65;
    C(7,7) = dCnm66;
    S(7,2) = dSnm61;
    S(7,3) = dSnm62;
    S(7,4) = dSnm63;
    S(7,5) = dSnm64;
    S(7,6) = dSnm65;
    S(7,7) = dSnm66;       

end
