% clear
% clc
% close all
% format long

%% Initializes MATLAB-ROS with Jetson Nano connections and variables
%{
© 2025 Yazan Chihabi
%}

%% Initialize ROS
disp('Initializing OBC...')
try
    rosnode list;
catch exp   % Error from rosnode list
    d = rosdevice('###.#.#.###','gnc','gnc123');
    runCore(d);
    
    ROS_MASTER_URI = 'http://###.#.#.###:11311/';
    ROS_IP = '###.#.#.###';
    setenv('ROS_MASTER_URI',ROS_MASTER_URI) % this should be verified by user
    setenv('ROS_IP',ROS_IP) % this should be verified by user
    rosinit(ROS_MASTER_URI);
end



%% Create Topics

Simulation_Clock_ROS = rospublisher("/Simulation_Clock","std_msgs/Float64","DataFormat","struct");
Clock_ROS = rospublisher("/Clock","std_msgs/Time","DataFormat","struct");
GNC_Run_ROS = rospublisher("/GNC_Run","std_msgs/Bool","DataFormat","struct");

Chaser_Force_ROS = rospublisher("/chaser/gnc/force","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Torque_ROS = rospublisher("/chaser/gnc/torque","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Vision_ROS = rospublisher("/chaser/sensors/vision","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_RADAR_ROS = rospublisher("/chaser/sensors/radar","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_TLE_OE_ROS = rospublisher("/chaser/sensors/tle/oe","std_msgs/Float64MultiArray","DataFormat","struct");
Chaser_TLE_time_ROS = rospublisher("/chaser/sensors/tle/time","std_msgs/UInt32MultiArray","DataFormat","struct");
Chaser_TLE_flag_ROS = rospublisher("/chaser/sensors/tle/flag","std_msgs/Bool","DataFormat","struct");
Chaser_Target_TLE_OE_ROS = rospublisher("/chaser/sensors/tle/target/oe","std_msgs/Float64MultiArray","DataFormat","struct");
Chaser_Target_TLE_time_ROS = rospublisher("/chaser/sensors/tle/target/time","std_msgs/UInt32MultiArray","DataFormat","struct");
Chaser_Target_TLE_flag_ROS = rospublisher("/chaser/sensors/tle/target/flag","std_msgs/Bool","DataFormat","struct");

Chaser_GPS_Position_ROS = rospublisher("/chaser/gps/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Velocity_ROS = rospublisher("/chaser/gps/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Acceleration_ROS = rospublisher("/chaser/gps/acceleration","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Time_ROS = rospublisher("/chaser/gps/time","std_msgs/UInt32MultiArray","DataFormat","struct");
Chaser_GPS_Status_ROS = rospublisher("/chaser/gps/status","std_msgs/Bool","DataFormat","struct");


Chaser_Position_ROS = rospublisher("/chaser/truth/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Velocity_ROS = rospublisher("/chaser/truth/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Position_ROS = rospublisher("/target/truth/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Velocity_ROS = rospublisher("/target/truth/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Attitude_ROS = rospublisher("/chaser/attitude/quaternion","geometry_msgs/QuaternionStamped","DataFormat","struct");
Chaser_AngRates_ROS = rospublisher("/chaser/attitude/rates","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Attitude_ROS = rospublisher("/target/attitude/quaternion","geometry_msgs/QuaternionStamped","DataFormat","struct");
Target_AngRates_ROS = rospublisher("/target/attitude/rates","geometry_msgs/Vector3Stamped","DataFormat","struct");

Sun_OE_ROS = rospublisher("/chaser/sensors/sun/oe","std_msgs/Float64MultiArray","DataFormat","struct");
Moon_OE_ROS = rospublisher("/chaser/sensors/moon/oe","std_msgs/Float64MultiArray","DataFormat","struct");

msg = rosmessage("geometry_msgs/Vector3Stamped","DataFormat","struct");
msg_quat = rosmessage("geometry_msgs/QuaternionStamped","DataFormat","struct");
msg_float = rosmessage("std_msgs/Float64","DataFormat","struct");
msg_Float64MultiArray = rosmessage("std_msgs/Float64MultiArray","DataFormat","struct");
msg_UInt32MultiArray = rosmessage("std_msgs/UInt32MultiArray","DataFormat","struct");
msg_UInt32 = rosmessage("std_msgs/UInt32","DataFormat","struct");
msg_bool = rosmessage("std_msgs/Bool","DataFormat","struct");
msg_time = rosmessage("std_msgs/Time","DataFormat","struct");

%% Creating ROS Properties parameters
ptree = rosparam;

ChaserProperties.mass = m2;
ChaserProperties.solar.coefficient = AuxilaryParameters.Cr2;
ChaserProperties.solar.area = AuxilaryParameters.area_solar2;
ChaserProperties.drag.coefficient = AuxilaryParameters.Cd2;
ChaserProperties.drag.area = AuxilaryParameters.area_drag2;

ChaserProperties.inertia.i11 = inertiaMatrix_Chaser(1,1);
ChaserProperties.inertia.i12 = inertiaMatrix_Chaser(1,2);
ChaserProperties.inertia.i13 = inertiaMatrix_Chaser(1,3);
ChaserProperties.inertia.i21 = inertiaMatrix_Chaser(2,1);
ChaserProperties.inertia.i22 = inertiaMatrix_Chaser(2,2);
ChaserProperties.inertia.i23 = inertiaMatrix_Chaser(2,3);
ChaserProperties.inertia.i31 = inertiaMatrix_Chaser(3,1);
ChaserProperties.inertia.i32 = inertiaMatrix_Chaser(3,2);
ChaserProperties.inertia.i33 = inertiaMatrix_Chaser(3,3);

ChaserProperties.inertia_inv.i11 = inertiaMatrix_Chaser_inv(1,1);
ChaserProperties.inertia_inv.i12 = inertiaMatrix_Chaser_inv(1,2);
ChaserProperties.inertia_inv.i13 = inertiaMatrix_Chaser_inv(1,3);
ChaserProperties.inertia_inv.i21 = inertiaMatrix_Chaser_inv(2,1);
ChaserProperties.inertia_inv.i22 = inertiaMatrix_Chaser_inv(2,2);
ChaserProperties.inertia_inv.i23 = inertiaMatrix_Chaser_inv(2,3);
ChaserProperties.inertia_inv.i31 = inertiaMatrix_Chaser_inv(3,1);
ChaserProperties.inertia_inv.i32 = inertiaMatrix_Chaser_inv(3,2);
ChaserProperties.inertia_inv.i33 = inertiaMatrix_Chaser_inv(3,3);

set(ptree,'ChaserProperties',ChaserProperties);

%% Creating ROS Hardware parameters
Hardware_OBC_flag = rospublisher("chaser/hardware/OBC/flag","std_msgs/Bool","DataFormat","struct");
Hardware_GPSsim_flag = rospublisher("chaser/hardware/GPSsim/flag","std_msgs/Bool","DataFormat","struct");
Hardware_GPSrec_flag = rospublisher("chaser/hardware/GPSrec/flag","std_msgs/Bool","DataFormat","struct");


%% Creating ROS GNC parameters
GNC_Nav_flag = rospublisher("/chaser/gnc/nav/flag","std_msgs/Bool","DataFormat","struct");
GNC_Ctl_flag = rospublisher("/chaser/gnc/ctl/flag","std_msgs/Bool","DataFormat","struct");
GNC_Guidance_flag = rospublisher("/chaser/gnc/guidance/flag","std_msgs/Bool","DataFormat","struct");


GNC.Ctl.Attitude.Kp = Kp_Attitude;
GNC.Ctl.Attitude.Kd = Kd_Attitude;

GNC.Ctl.Position.LQR.K11 = K_lqr(1,1);
GNC.Ctl.Position.LQR.K12 = K_lqr(1,2);
GNC.Ctl.Position.LQR.K13 = K_lqr(1,3);
GNC.Ctl.Position.LQR.K14 = K_lqr(1,4);
GNC.Ctl.Position.LQR.K15 = K_lqr(1,5);
GNC.Ctl.Position.LQR.K16 = K_lqr(1,6);

GNC.Ctl.Position.LQR.K21 = K_lqr(2,1);
GNC.Ctl.Position.LQR.K22 = K_lqr(2,2);
GNC.Ctl.Position.LQR.K23 = K_lqr(2,3);
GNC.Ctl.Position.LQR.K24 = K_lqr(2,4);
GNC.Ctl.Position.LQR.K25 = K_lqr(2,5);
GNC.Ctl.Position.LQR.K26 = K_lqr(2,6);

GNC.Ctl.Position.LQR.K31 = K_lqr(3,1);
GNC.Ctl.Position.LQR.K32 = K_lqr(3,2);
GNC.Ctl.Position.LQR.K33 = K_lqr(3,3);
GNC.Ctl.Position.LQR.K34 = K_lqr(3,4);
GNC.Ctl.Position.LQR.K35 = K_lqr(3,5);
GNC.Ctl.Position.LQR.K36 = K_lqr(3,6);

GNC.Guidance.Time.Rendezvous = T_Rendezvous;
GNC.Guidance.Time.Terminal   = T_Terminal;
GNC.Guidance.Time.Formation  = T_Formation;

set(ptree,'GNC',GNC);

%% Creating ROS Sensor parameters

Sensor_Vision_flag_ROS = rospublisher("chaser/sensor/vision/flag","std_msgs/Bool","DataFormat","struct");
Sensor_RADAR_flag_ROS = rospublisher("chaser/sensor/RADAR/flag","std_msgs/Bool","DataFormat","struct");
Sensor_TLE_flag_ROS = rospublisher("chaser/sensor/TLE/flag","std_msgs/Bool","DataFormat","struct");
Sensor_GPS_flag_ROS = rospublisher("chaser/sensor/GPS/flag","std_msgs/Bool","DataFormat","struct");


%% Creating ROS physics parameters
set(ptree,'ConstantParameters',ConstantParameters);
set(ptree,'AuxilaryParameters',AuxilaryParameters);
set(ptree,'Earth/thetaGMT',thetaGMTini);
% set(ptree,'Earth/Cnm',Cnm_struct);
% set(ptree,'Earth/Snm',Snm_struct);

%% Creating ROS Hardware parameters
set(ptree,'hardware/rate',dt)

%% Generate ROS Lists

msglist = rosmsg("list");
actionlist = rosaction("list");
svclist = rosservice("list");
topiclist = rostopic("list");
nodelist = rosnode("list")';
paramlist = rosparam("list");

%% Subscribers
Chaser_Force_ROS_sub = rossubscriber("/chaser/gnc/force","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Torque_ROS_sub = rossubscriber("/chaser/gnc/torque","geometry_msgs/Vector3Stamped","DataFormat","struct");

Rel_Position_Est_ROS = rossubscriber("/chaser/gnc/nav/relative/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Rel_Velocity_Est_ROS = rossubscriber("/chaser/gnc/nav/relative/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Position_Est_ROS = rossubscriber("/chaser/gnc/nav/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Velocity_Est_ROS = rossubscriber("/chaser/gnc/nav/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Position_Est_ROS = rossubscriber("/chaser/gnc/nav/target/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Velocity_Est_ROS = rossubscriber("/chaser/gnc/nav/target/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Rel_EKF_ROS_sub   = rossubscriber("/chaser/gnc/nav/relative/EKF","std_msgs/Float64MultiArray","DataFormat","struct");
Chaser_GPS_EKF_ROS_sub   = rossubscriber("/chaser/gnc/nav/GPS/EKF","std_msgs/Float64MultiArray","DataFormat","struct");

% Attitude Topics
Chaser_DesiredAttitude_ROS_sub = rossubscriber("/chaser/gnc/attitude/desired","geometry_msgs/QuaternionStamped","DataFormat","struct");
Chaser_AttitudeError_ROS_sub = rossubscriber("/chaser/gnc/attitude/quaternion/error","geometry_msgs/QuaternionStamped","DataFormat","struct");

% Guidance topics
Rel_Position_Guidance_ROS_sub = rossubscriber("/chaser/gnc/guidance/relative/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Rel_Velocity_Guidance_ROS_sub = rossubscriber("/chaser/gnc/guidance/relative/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");


%% Initialize Topics
ROS_fcns.publish_time2ros(Clock_ROS,msg_time,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_data2ros(GNC_Run_ROS,msg_bool,false);

ROS_fcns.publish_vector2ros(Chaser_Force_ROS,msg,[0;0;0],uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Chaser_Torque_ROS,msg,[0;0;0],uint32([posix_time_sec;posix_time_nsec]));

ROS_fcns.publish_vector2ros(Chaser_GPS_Position_ROS,msg,r2_I_ini,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Chaser_GPS_Velocity_ROS,msg,v2_I_ini,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Chaser_GPS_Acceleration_ROS,msg,a2_I_ini,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_data2ros(Chaser_GPS_Time_ROS,msg_UInt32MultiArray, uint32([GPS_week;GPS_time]));
ROS_fcns.publish_data2ros(Chaser_GPS_Status_ROS,msg_bool,false);

ROS_fcns.publish_vector2ros(Chaser_Position_ROS,msg,r2_I_prop,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Chaser_Velocity_ROS,msg,v2_I_prop,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Target_Position_ROS,msg,r1_I_prop,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_vector2ros(Target_Velocity_ROS,msg,v1_I_prop,uint32([posix_time_sec;posix_time_nsec]));

ROS_fcns.publish_data2ros(Simulation_Clock_ROS,msg_float,0);
ROS_fcns.publish_data2ros(Chaser_TLE_time_ROS,msg_UInt32MultiArray,uint32(UTC_initial));
ROS_fcns.publish_data2ros(Chaser_TLE_OE_ROS,msg_Float64MultiArray,TLE_prop);
ROS_fcns.publish_data2ros(Chaser_TLE_flag_ROS,msg_bool,TLE_update);
ROS_fcns.publish_data2ros(Chaser_Target_TLE_time_ROS,msg_UInt32MultiArray,uint32(UTC_initial));
ROS_fcns.publish_data2ros(Chaser_Target_TLE_OE_ROS,msg_Float64MultiArray,TLE_prop_target);
ROS_fcns.publish_data2ros(Chaser_Target_TLE_flag_ROS,msg_bool,TLE_update);


ROS_fcns.publish_vector2ros(Target_AngRates_ROS,msg,Target_AngularVelocity_prop,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_quat2ros(Target_Attitude_ROS,msg_quat,Target_Attitude_prop,uint32([posix_time_sec;posix_time_nsec]));

ROS_fcns.publish_vector2ros(Chaser_AngRates_ROS,msg,Chaser_AngularVelocity_prop,uint32([posix_time_sec;posix_time_nsec]));
ROS_fcns.publish_quat2ros(Chaser_Attitude_ROS,msg_quat,Chaser_Attitude_prop,uint32([posix_time_sec;posix_time_nsec]));

ROS_fcns.publish_data2ros(Sun_OE_ROS,msg_Float64MultiArray,[oe_sun(:,1);tanos(1)]);
ROS_fcns.publish_data2ros(Moon_OE_ROS,msg_Float64MultiArray,[oe_moon(:,1);tanom(1)]);
%% Generate GNC Node
cfg = coder.config('exe');
cfg.Hardware = coder.hardware('Robot Operating System (ROS)');
cfg.Hardware.BuildAction = 'Build and run';
cfg.Hardware.RemoteDeviceAddress = '###.#.#.###';
cfg.Hardware.RemoteDeviceUsername = 'gnc';
cfg.Hardware.RemoteDevicePassword = 'gnc123';
cfg.Hardware.DeployTo = 'Remote Device';
cfg.Hardware.CatkinWorkspace = '~/catkin_ws';
codegen ChaserGNC_Template -args {} -config cfg

disp('OBC initialized')