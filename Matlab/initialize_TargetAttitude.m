%{
© 2025 Yazan Chihabi
%}

%% Target Attitude Initialization
%% Initial angular rate and quaternion
initialAngularVelocity_Target =1*[0.1; 0.1; 0.1]; % rad/s
Target_AngularVelocity_prop = initialAngularVelocity_Target;
% initialAngularVelocity= [10;10;10]*d2r;
initialAttitude_Target = [0.2652; 0.2652; -0.6930; 0.6157]; % Arbitrary values
Target_Attitude_prop = initialAttitude_Target;
%% Calculating Inertia Matrix (Chaser)
z = 2; % m
y = 1.5; % m
x = 1; % m

Ix = (m1/12)*(y^2+z^2);
Iy = (m1/12)*(x^2+z^2);
Iz = (m1/12)*(x^2+y^2);

inertiaMatrix_Target = [Ix, 0, 0;
                0, Iy, 0;
                0, 0, Iz]; % kg*m^2;


inertiaMatrix_Target_inv = inertiaMatrix_Target^-1;
