%% Main Functions
% Propagates the inertial states of a S/C
function X  = simulator(t,states, Cnm, Snm, ConstantParameters, AuxilaryParameters, ...
    MJD_initial, centralbody,  eopdata, PC, flag_sc, u)
%{
© 2025 Yazan Chihabi
%}
aI = [0;0;0];
rI = states(1:3);
vI = states(4:6);

aI = aI + u;

flag = centralbody;

[UT1,DJMJD0,~,TT,~,Mjd_UTC,r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, ...
 r_Neptune,r_Pluto,r_Moon,r_Sun,r_SunSSB,E,~,TT_UTC,x_pole,y_pole,~] = time_variables.Julian_time(t, MJD_initial, centralbody, ConstantParameters, eopdata, PC);

r = sqrt(rI(1)^2 + rI(2)^2 + rI(3)^2);
v = sqrt(vI(1)^2 + vI(2)^2 + vI(3)^2);
mu_Earth   = 398600.4418;         % [km^3/s^2]; WGS-84
mu_Sun     = 132712440041.939377; % [km^3/s^2]; DE436
mu_Moon    = 4902.800117;         % [km^3/s^2]; DE436
mu_Mercury = 22031.780000;  	  % [km^3/s^2]; DE436
mu_Venus   = 324858.592000;       % [km^3/s^2]; DE436
mu_Mars    = 42828.375214; 	  	  % [km^3/s^2]; DE436
mu_Jupiter = 126712764.133446;    % [km^3/s^2]; DE436
mu_Saturn  = 37940585.200000;     % [km^3/s^2]; DE436
mu_Uranus  = 5794556.465752;      % [km^3/s^2]; DE436
mu_Neptune = 6836527.100580;      % [km^3/s^2]; DE436
mu_Pluto   = 975.501176;   		  % [km^3/s^2]; DE436
c_light = ConstantParameters.c_light;
rE = ConstantParameters.R_Earth;
nmax = flag(9);
nmin = flag(10);
C = Cnm;
S = Snm;

if flag_sc == 1
    Adrag = AuxilaryParameters.area_drag1;
    Cd = AuxilaryParameters.Cd1;
    Asolar = AuxilaryParameters.area_solar1;
    Cr = AuxilaryParameters.Cr1;
    mass = AuxilaryParameters.mass1;
else
    Adrag = AuxilaryParameters.area_drag2;
    Cd = AuxilaryParameters.Cd2;
    Asolar = AuxilaryParameters.area_solar2;
    Cr = AuxilaryParameters.Cr2;
    mass = AuxilaryParameters.mass2;
end

%Perturbations
if flag(1) == 1 % Luni-Solar third body
    aI = dynamics.ThirdBodyPerturbation(rI, r_Moon, mu_Moon) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Sun, mu_Sun) + aI;
end
if flag(3) == 1 % Planetary third body
    aI = dynamics.ThirdBodyPerturbation(rI, r_Mercury, mu_Mercury) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Venus, mu_Venus) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Mars, mu_Mars) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Jupiter, mu_Jupiter) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Saturn, mu_Saturn) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Uranus, mu_Uranus) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Neptune, mu_Neptune) + aI;
    aI = dynamics.ThirdBodyPerturbation(rI, r_Pluto, mu_Pluto) + aI;
end
if flag(4) == 1 %atmospheric drag (exponential density model)
    rmod = r;
    h = rmod - rE; %altitude
    h0 = 0; %reference altitude
    H = 1; %scale altitude
    rho0 = 0;

    if h>=100 && h<110
        rho0 = 5.297*(10^-7);
        H = 5.877;
        h0 = 100;
    end
    if h>=110 && h<120
        rho0 = 9.661*(10^-8);
        H = 7.263;
        h0 = 110;
    end
    if h>=120 && h<130
        rho0 = 2.438*(10^-8);
        H = 9.473;
        h0 = 120;
    end
    if h>=130 && h<140
        rho0 = 8.484*(10^-9);
        H = 12.636;
        h0 = 130;
    end
    if h>=140 && h<150
        rho0 = 3.845*(10^-9);
        H = 16.149;
        h0 = 140;
    end
    if h>=150 && h<180
        rho0 = 2.070*(10^-9);
        H = 22.523;
        h0 = 150;
    end
    if h>=180 && h<200
        rho0 = 5.464*(10^-10);
        H = 29.740;
        h0 = 180;
    end
    if h>=200 && h<250
        rho0 = 2.789*(10^-10);
        H = 37.105;
        h0 = 200;
    end
    if h>=250 && h<300
        rho0 = 7.248*(10^-11);
        H = 45.546;
        h0 = 250;
    end
    if h>=300 && h<350
        rho0 = 2.418*(10^-11);
        H = 53.628;
        h0 = 300;
    end
    if h>=350 && h<400
        rho0 = 9.518*(10^-12);
        H = 53.298;
        h0 = 350;
    end
    if h>=400 && h<450
        rho0 = 3.725*(10^-12);
        H = 58.515;
        h0 = 400;
    end
    if h>=450 && h<500
        rho0 = 1.585*(10^-12);
        H = 60.828;
        h0 = 450;
    end
    if h>=500 && h<600
        rho0 = 6.967*(10^-13);
        H = 63.822;
        h0 = 500;
    end
    if h>=600 && h<700
        rho0 = 1.454*(10^-13);
        H = 71.835;
        h0 = 600;
    end
    if h>=700 && h<800
        rho0 = 3.614*(10^-14);
        H = 88.667;
        h0 = 700;
    end
    if h>=800 && h<900
        rho0 = 1.170*(10^-14);
        H = 124.64;
        h0 = 800;
    end
    if h>=900 && h<1000
        rho0 = 5.245*(10^-15);
        H = 181.05;
        h0 = 900;
    end
    if h>=1000
        rho0 = 3.019*(10^-15);
        H = 268;
        h0 = 1000;
    end

    rho = rho0*exp(-(h-h0)/H); %density
    wE = ConstantParameters.omega_Earth; %rotation of the Earth
    aI = dynamics.Drag(rho,rI,vI,Adrag,mass,Cd,wE)  + aI;
end
if flag(5) == 1 % SRP
    aI = dynamics.SolarRadiationPressure(rI,r_Earth,r_Moon,r_Sun,r_SunSSB,Asolar,mass,Cr,ConstantParameters.P_Sol,ConstantParameters.AU,'geometrical',ConstantParameters) + aI;
end
if flag(6) == 1 % RelativisticPerturbation
    aI = dynamics.RelativisticPerturbation(rI, vI, r_Sun, [0;0;0], mu_Earth, mu_Sun, c_light, [0;0;980]) + aI;
end
if flag(2) == 1 % gravitational field 
    r_Moon = E*r_Moon;
    [lM, phiM, rM] = time_variables.CalcPolarAngles(r_Moon);
    r_Sun = E*r_Sun;
    [lS, phiS, rS] = time_variables.CalcPolarAngles(r_Sun);

    Mjd_TT = Mjd_UTC + TT_UTC/86400;
    T  = (Mjd_TT-ConstantParameters.MJD_J2000)/36525;
    T2 = T*T;
    T3 = T2*T;
    theta_g = time_variables.iauGmst06(DJMJD0, UT1, DJMJD0, TT, ConstantParameters);
    r_ref = ConstantParameters.R_Earth; 
    if flag(7) == 1 % Solid tides
        [dC1,dS1] = dynamics.SolidTides(T,T2,T3,phiM,phiS,mu_Moon,mu_Sun,mu_Earth,r_ref,rS,rM,lS,lM,theta_g,x_pole,y_pole);
        S(1:5,1:4) = S(1:5,1:4) + dS1;
        C(1:5,1:4) = C(1:5,1:4) + dC1;
    elseif flag(8) == 1 %ocean tides
        [dC2,dS2] = dynamics.OceanTides(phiM,phiS,mu_Moon,mu_Sun,mu_Earth,r_ref,rS,rM,lS,lM);
        S(1:7,1:7) = S(1:7,1:7) + dS2;
        C(1:7,1:7) = C(1:7,1:7) + dC2;
    end
    aI = dynamics.GravityFieldPerturbiation(rI,r,E,nmax,nmin,C,S,mu_Earth,rE) + aI;
end
if flag(2) == 0 % two-body equation
    aI = -mu_Earth/(r^3).*rI + aI;
end

X = [vI;aI];
end

