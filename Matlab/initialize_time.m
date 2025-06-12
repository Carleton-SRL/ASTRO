%{
© 2025 Yazan Chihabi
%}

dt =1;
dt_data = 1;
dt_GPS = 0.02;

T_Rendezvous = 2*T1;
T_Terminal = 0*T1;
T_Formation = 0*T1;

Tfinal = T_Rendezvous + T_Terminal + T_Formation;

t = 0:dt:Tfinal;

tpropGPS = 0:dt_GPS:dt_data;
tpropGPS_length = length(tpropGPS);

GPS_TimeStamps_Receiver = zeros(2,length(t));
GPS_TimeStamps_Simulator = zeros(2,length(t));

% Initial Julian Date
[x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = time_variables.IERS(eopdata,MJD_UTC0,'l',ConstantParameters);
[UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = time_variables.timediff(UT1_UTC,TAI_UTC);

JD0 =  MJD_UTC0+2400000.5;

JD = JD0;
MJD_UTC = MJD_UTC0;

year = UTC_initial(1);
month = UTC_initial(2);
day = UTC_initial(3);
hour = UTC_initial(4);
minute = UTC_initial(5);
sec = UTC_initial(6); 
[DJMJD0, DATE] = time_variables.iauCal2jd(year, month, day);
TIME = (60*(60*hour + minute) + sec)/86400;
UTC = DATE + TIME;
TT = UTC + TT_UTC/86400;
TUT = TIME + UT1_UTC/86400;
UT1 = DATE + TUT;

% Greenwich sidreal time (Greenwich angle with respect to the inertial Ix axis)
[~,thetaGMT] = siderealTime(juliandate(UTC_initial));
thetaGMT = thetaGMT.*d2r;
thetaGMTini = thetaGMT;
wE = ConstantParameters.omega_Earth-0.843994809*1e-9*LOD;
wEx = skew_matrix([0;0;wE]);

% Initial GPS Time
[GPS_week,GPS_time] = GPS_Simulator.GPSTime(UTC_initial);
GPS_TimeStamps_Simulator(:,1) = [GPS_week;GPS_time*1000];

MJD_initial = MJD_UTC;

% Posix time
posix_time_ini = posixtime(datetime(UTC_initial));
posix_time_prop = posix_time_ini;

posix_time_sec = uint32(floor(posix_time_prop));
posix_time_nsec = uint32((posix_time_prop-floor(posix_time_prop))*1e9);
ROS_time = [posix_time_sec;posix_time_nsec];

% Chaser & Target States
StateVars_Chaser = zeros(6,length(t));
StateVars_Target = zeros(6,length(t));
Control_Chaser   = zeros(6,length(t));
Control_Target   = zeros(6,length(t));

% Guidance
RelativeStates_guidance = zeros(6,length(t));
ChaserAttitude_Desired = zeros(4,length(t));

% Control
ChaserAttitude_Error = zeros(4,length(t));

% Navigation
Chaser_Rel_EKF = zeros(42,length(t));
Chaser_GPS_EKF = zeros(42,length(t));
