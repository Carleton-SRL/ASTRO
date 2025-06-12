%--------------------------------------------------------------------------
%
% SAT_Const: Constant Values used in the propagation of s/c states
%
%
%
%--------------------------------------------------------------------------
%{
© 2025 Yazan Chihabi
%}


% Mathematical constants
ConstantParameters.pi2       = 2*pi;                % 2pi
ConstantParameters.Rad       = pi/180;              % Radians per degree
ConstantParameters.Deg       = 180/pi;              % Degrees per radian
ConstantParameters.Arcs      = 3600*180/pi;         % Arcseconds per radian

% General
ConstantParameters.MJD_J2000 = 51544.5;             % Modified Julian Date of J2000
ConstantParameters.T_B1950   = -0.500002108;        % Epoch B1950
ConstantParameters.c_light   = 299792.457999999984; % Speed of light  [km/s]; DE436
ConstantParameters.AU        = 149597870.699999988; % Astronomical unit [km]; DE436

% Physical parameters of the Earth, Sun and Moon

% Equatorial radius and flattening
ConstantParameters.R_Earth   = 6378.137;          % Earth's radius [km]; WGS-84
ConstantParameters.f_Earth   = 1/298.257223563;     % Flattening; WGS-84
ConstantParameters.R_Sun     = 696000;            % Sun's radius [km]; DE436
ConstantParameters.R_Moon    = 1738;              % Moon's radius [km]; DE436

% Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
ConstantParameters.omega_Earth = 15.04106717866910/3600*ConstantParameters.Rad; % [rad/s]; WGS-84

% Gravitational coefficients
ConstantParameters.mu_Earth   = 398600.4418;         % [km^3/s^2]; WGS-84
ConstantParameters.mu_Sun     = 132712440041.939377; % [km^3/s^2]; DE436
ConstantParameters.mu_Moon    = 4902.800117;         % [km^3/s^2]; DE436
ConstantParameters.mu_Mercury = 22031.780000;  	  % [km^3/s^2]; DE436
ConstantParameters.mu_Venus   = 324858.592000;       % [km^3/s^2]; DE436
ConstantParameters.mu_Mars    = 42828.375214; 	  	  % [km^3/s^2]; DE436
ConstantParameters.mu_Jupiter = 126712764.133446;    % [km^3/s^2]; DE436
ConstantParameters.mu_Saturn  = 37940585.200000;     % [km^3/s^2]; DE436
ConstantParameters.mu_Uranus  = 5794556.465752;      % [km^3/s^2]; DE436
ConstantParameters.mu_Neptune = 6836527.100580;      % [km^3/s^2]; DE436
ConstantParameters.mu_Pluto   = 975.501176;   		  % [km^3/s^2]; DE436

% Solar radiation pressure at 1 AU
ConstantParameters.P_Sol = 1.367/ConstantParameters.c_light; % [kN/m^2] (1.367 kW/m^2); IERS

