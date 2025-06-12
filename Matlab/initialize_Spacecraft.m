%{
© 2025 Yazan Chihabi
%}

%Spacecraft constants
CD = 2.3;AuxilaryParameters.Cd1 = CD;AuxilaryParameters.Cd2 = CD;
CR = 2;AuxilaryParameters.Cr1 = CR;AuxilaryParameters.Cr2 = CR;
%Chaser
m2 = 350;AuxilaryParameters.mass2 = m2;
SA2 = 3.5;AuxilaryParameters.area_drag2 = SA2;AuxilaryParameters.area_solar2 = SA2;
%Target
m1 = 339;AuxilaryParameters.mass1 = m1;
SA1 = 3.34;AuxilaryParameters.area_drag1 = SA1;AuxilaryParameters.area_solar1 = SA1;

% Target S/C initial osculating orbital elements
% Alouette - 2 (From tle) %note that this assumes that the elements
% from the .txt file are osculating, and not mean elements.
fname = 'TLE/ISS_tle.txt';
% fname = 'TLE/alouette2_tle.txt';
[a1,e1,w1,i1,RAAN1,tano1,M1,~] = TLERead(fname,mu);
%Target
% m1 = CD*SA1/B1;AuxilaryParameters.mass1 = m1;


% or use this for custom osculating orbital elements
% a1       = 7000; %km
% e1       = 0.05;
% i1       = 90*d2r; %rad
% w1       = 350*d2r; %rad
% RAAN1    = 100*d2r; %rad
% tano1    = 100*d2r; %rad
% 
% E1 = 2*atan(sqrt((1-e1)/(1+e1))*tan(tano1/2));
% M1 = E1 - e1*sin(E1);
% date vector as [Y, M, D, H, MN, S]
% Y = 2020;
% Mo = 06;
% D = 17;
% H = 00;
% MN = 30;
% SC = 0;
% Mjd0 = Mjday(Y, Mo, D, H, MN, SC);
% UTC_initial = [Y, Mo, D, H, MN, SC];
% assignin('base','UTC_initial',UTC_initial)
% assignin('base','MJD_UTC0',Mjd0)
% month_ini = month2char(Mo);
% assignin('base','t0',append(num2str(D),' ',month_ini,' ',num2str(Y),' ',num2str(H),':',num2str(MN),':',num2str(SC)));
    
if i1>pi/2
    orbit = 'retro';
else
    orbit = 'pro';
end

% Is target maneuvering? 1 for yes 0 for no
maneuvering_target = 0;

oe1      = [a1,e1,i1,w1,RAAN1,tano1];
p1       = a1*(1-e1^2); %km
r1       = p1/(1+e1*cos(tano1)); % km
T1       = round(sqrt(((4*pi^2)*a1^3)/mu));
n1 = sqrt(mu/(a1^3));

% % Chaser initial relative orbital elements
% xinitial = [-15;2e-05;6e-04;2e-02;8e-03;-4e-02];
% xinitial = [-100;-4e-01;-5*d2r;-0.4*d2r;1*d2r;-10*d2r];
% xinitial = [-500;-4e-05;-25*d2r;-10*d2r;10*d2r;-1*d2r];
% xinitial = [-10;-4e-05;-0.05*d2r;-0.01*d2r;0.01*d2r;-0.02*d2r];
% xinitial = [-10;-4e-05;-0.5*d2r;-0.1*d2r;0.1*d2r;-0.2*d2r];
% xinitial = [-0.5;-5e-04;-2*d2r;-1*d2r;1*d2r;5*d2r];
xinitial = [-0.5;-5e-04;-1*d2r;-1*d2r;1*d2r;-0.2*d2r];
% xinitial = [-15;2e-05;0.05*d2r;0.01*d2r;0.01*d2r;-0.02*d2r];
% xinitial = [-2;2e-05;6e-05;2e-05;8e-05;-1e-05];
% xinitial = [-25;2e-04;6e-03;2e-02;8e-02;-4e-01];
% xinitial = [0;0;0;0;0;0.00000001];
% xinitial = [0;0;0;0;0;0];

% Chaser initial osculating orbital elements
a2 = a1 + xinitial(1);
e2 = e1 + xinitial(2);
i2 = i1 + xinitial(3);
w2 = w1 + xinitial(4);
RAAN2 = RAAN1 + xinitial(5);
M2 = M1 + xinitial(6);
M2       = mod(M2, 2*pi);

[tano2,E2] = dynamics.M2tano(M2,e2,50);

p2 = a2*(1-e2^2);
r2 = p2/(1+e2*cos(tano2));
oe2      = [a2,e2,i2,w2,RAAN2,tano2];
n2 = sqrt(mu/((a2)^3));

% Initial inertial position and velocity of S/C 1 (target), no offset
[r1_I_ini,v1_I_ini] = Rotations.OE2ECI(oe1,mu);

% Initial inertial position and velocity of S/C 2 (chaser)
[r2_I_ini,v2_I_ini] = Rotations.OE2ECI(oe2,mu);


%% Ballistic Coefficients

BSRP_t = CR*SA1/m1;
Bdrag_t = CD*SA1/m1;

BSRP_c = CR*SA2/m2;
Bdrag_c = CD*SA2/m2;

dBSRP = CR*(SA2/m2 - SA1/m1);

%% Attitude
initialize_ChaserAttitude
initialize_TargetAttitude