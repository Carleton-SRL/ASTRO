%{
© 2025 Yazan Chihabi
%}

%% Chaser Attitude Initialization
%% Initial angular rate and quaternion
initialAngularVelocity_Chaser =0*[0.1; 0.1; 0.1]; % rad/s
Chaser_AngularVelocity_prop = initialAngularVelocity_Chaser;
% initialAngularVelocity= [10;10;10]*d2r;
initialAttitude_Chaser = [0.2652; 0.2652; -0.6930; 0.6157]; % Arbitrary values
Chaser_Attitude_prop = initialAttitude_Chaser;
%% Calculating Inertia Matrix (Chaser)
z = 2.5; % m
y = 1.5; % m
x = 1; % m

Ix = (m2/12)*(y^2+z^2);
Iy = (m2/12)*(x^2+z^2);
Iz = (m2/12)*(x^2+y^2);

inertiaMatrix_Chaser = [Ix, 0, 0;
                0, Iy, 0;
                0, 0, Iz]; % kg*m^2;

inertiaMatrix_Chaser_inv = inertiaMatrix_Chaser^-1;
%% Body-fixed thruster parameters

thruster_unitVector = [0;0;1];



