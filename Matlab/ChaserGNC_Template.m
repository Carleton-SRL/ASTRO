function ChaserGNC_Template
%{
This code is a template for the Chaser's GNC used for ROS node generation
on a ROS enabled hardware. The node can be generated internally onto
MATLAB's built in ROS server or onto an external hardware provided ROS is
installed on it. 

This code serves as a template for future users to deploy their own GNC
algorithms for testing purposes.

© 2025 Yazan Chihabi

%}

%% Parameters

Ix = [1;0;0];
Iy = [0;1;0];
Iz = [0;0;1];

% Properties
m = rosparam("get","ChaserProperties/mass");

[inertiaMatrix_Chaser,inertiaMatrix_Chaser_inv] = ROS_fcns.Parameters.Inertia_Properties();

ConstantParameters = ROS_fcns.Parameters.Physics_Constants();

dt = rosparam("get","hardware/rate");


% Attitude Controller
Kp_Attitude = rosparam("get","GNC/Ctl/Attitude/Kp");
Kd_Attitude = rosparam("get","GNC/Ctl/Attitude/Kd");

% Position Controller (LQR)
K_lqr = zeros(3,6);
K_lqr(1,1) = rosparam("get","GNC/Ctl/Position/LQR/K11");
K_lqr(1,2) = rosparam("get","GNC/Ctl/Position/LQR/K12");
K_lqr(1,3) = rosparam("get","GNC/Ctl/Position/LQR/K13");
K_lqr(1,4) = rosparam("get","GNC/Ctl/Position/LQR/K14");
K_lqr(1,5) = rosparam("get","GNC/Ctl/Position/LQR/K15");
K_lqr(1,6) = rosparam("get","GNC/Ctl/Position/LQR/K16");

K_lqr(2,1) = rosparam("get","GNC/Ctl/Position/LQR/K21");
K_lqr(2,2) = rosparam("get","GNC/Ctl/Position/LQR/K22");
K_lqr(2,3) = rosparam("get","GNC/Ctl/Position/LQR/K23");
K_lqr(2,4) = rosparam("get","GNC/Ctl/Position/LQR/K24");
K_lqr(2,5) = rosparam("get","GNC/Ctl/Position/LQR/K25");
K_lqr(2,6) = rosparam("get","GNC/Ctl/Position/LQR/K26");

K_lqr(3,1) = rosparam("get","GNC/Ctl/Position/LQR/K31");
K_lqr(3,2) = rosparam("get","GNC/Ctl/Position/LQR/K32");
K_lqr(3,3) = rosparam("get","GNC/Ctl/Position/LQR/K33");
K_lqr(3,4) = rosparam("get","GNC/Ctl/Position/LQR/K34");
K_lqr(3,5) = rosparam("get","GNC/Ctl/Position/LQR/K35");
K_lqr(3,6) = rosparam("get","GNC/Ctl/Position/LQR/K36");

%% Topics

% Flags
Hardware_OBC_flag_sub = rossubscriber("chaser/hardware/OBC/flag","std_msgs/Bool","DataFormat","struct");
Hardware_GPSsim_flag_sub = rossubscriber("chaser/hardware/GPSsim/flag","std_msgs/Bool","DataFormat","struct");
Hardware_GPSrec_flag_sub = rossubscriber("chaser/hardware/GPSrec/flag","std_msgs/Bool","DataFormat","struct");

GNC_Nav_flag_sub = rossubscriber("/chaser/gnc/nav/flag","std_msgs/Bool","DataFormat","struct");
GNC_Ctl_flag_sub = rossubscriber("/chaser/gnc/ctl/flag","std_msgs/Bool","DataFormat","struct");
GNC_Guidance_flag_sub = rossubscriber("/chaser/gnc/guidance/flag","std_msgs/Bool","DataFormat","struct");

Sensor_Vision_flag_ROS_sub = rossubscriber("chaser/sensor/vision/flag","std_msgs/Bool","DataFormat","struct");
Sensor_RADAR_flag_ROS_sub = rossubscriber("chaser/sensor/RADAR/flag","std_msgs/Bool","DataFormat","struct");
Sensor_TLE_flag_ROS_sub = rossubscriber("chaser/sensor/TLE/flag","std_msgs/Bool","DataFormat","struct");
Sensor_GPS_flag_ROS_sub = rossubscriber("chaser/sensor/GPS/flag","std_msgs/Bool","DataFormat","struct");

% Nav topics
Chaser_Attitude_ROS_sub = rossubscriber("/chaser/attitude/quaternion","geometry_msgs/QuaternionStamped","DataFormat","struct");
Chaser_AngRates_ROS_sub = rossubscriber("/chaser/attitude/rates","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Attitude_ROS_sub = rossubscriber("/target/attitude/quaternion","geometry_msgs/QuaternionStamped","DataFormat","struct");
Target_AngRates_ROS_sub = rossubscriber("/target/attitude/rates","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Vision_ROS_sub   = rossubscriber("/chaser/sensors/vision","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_RADAR_ROS_sub    = rossubscriber("/chaser/sensors/radar","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_TLE_OE_ROS_sub   = rossubscriber("/chaser/sensors/tle/oe","std_msgs/Float64MultiArray","DataFormat","struct");
Chaser_TLE_time_ROS_sub = rossubscriber("/chaser/sensors/tle/time","std_msgs/UInt32MultiArray","DataFormat","struct");
Chaser_TLE_flag_ROS_sub = rossubscriber("/chaser/sensors/tle/flag","std_msgs/Bool","DataFormat","struct");

Chaser_GPS_Position_ROS_sub     = rossubscriber("/chaser/gps/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Velocity_ROS_sub     = rossubscriber("/chaser/gps/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Acceleration_ROS_sub = rossubscriber("/chaser/gps/acceleration","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_GPS_Time_ROS_sub         = rossubscriber("/chaser/gps/time","std_msgs/UInt32MultiArray","DataFormat","struct");
Chaser_GPS_Status_ROS_sub       = rossubscriber("/chaser/gps/status","std_msgs/Bool","DataFormat","struct");

Chaser_Position_ROS_sub = rossubscriber("/chaser/truth/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Velocity_ROS_sub = rossubscriber("/chaser/truth/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Position_ROS_sub = rossubscriber("/target/truth/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Velocity_ROS_sub = rossubscriber("/target/truth/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Position_Est_Error_ROS = rospublisher("/chaser/gnc/nav/position/error","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Velocity_Est_Error_ROS = rospublisher("/chaser/gnc/nav/velocity/error","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Position_Est_Error_ROS = rospublisher("/chaser/gnc/nav/target/position/error","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Velocity_Est_Error_ROS = rospublisher("/chaser/gnc/nav/target/velocity/error","geometry_msgs/Vector3Stamped","DataFormat","struct");

Chaser_Position_Est_ROS = rospublisher("/chaser/gnc/nav/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Velocity_Est_ROS = rospublisher("/chaser/gnc/nav/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Position_Est_ROS = rospublisher("/chaser/gnc/nav/target/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Target_Velocity_Est_ROS = rospublisher("/chaser/gnc/nav/target/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

Sun_OE_ROS_sub = rossubscriber("/chaser/sensors/sun/oe","std_msgs/Float64MultiArray","DataFormat","struct");
Moon_OE_ROS_sub = rossubscriber("/chaser/sensors/moon/oe","std_msgs/Float64MultiArray","DataFormat","struct");


% Control topics
Chaser_Force_ROS         = rospublisher("/chaser/gnc/force","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Torque_ROS        = rospublisher("/chaser/gnc/torque","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_AttitudeError_ROS = rospublisher("/chaser/gnc/attitude/quaternion/error","geometry_msgs/QuaternionStamped","DataFormat","struct");
Chaser_PositionError_ROS = rospublisher("/chaser/gnc/guidance/position/error","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_VelocityError_ROS = rospublisher("/chaser/gnc/guidance/velocity/error","geometry_msgs/Vector3Stamped","DataFormat","struct");

% Relative navigation topics
Rel_Position_Est_ROS = rospublisher("/chaser/gnc/nav/relative/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Rel_Velocity_Est_ROS = rospublisher("/chaser/gnc/nav/relative/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");
Chaser_Rel_EKF_ROS   = rospublisher("/chaser/gnc/nav/relative/EKF","std_msgs/Float64MultiArray","DataFormat","struct");
Chaser_GPS_EKF_ROS   = rospublisher("/chaser/gnc/nav/GPS/EKF","std_msgs/Float64MultiArray","DataFormat","struct");

% Guidance topics
Rel_Position_Guidance_ROS = rospublisher("/chaser/gnc/guidance/relative/position","geometry_msgs/Vector3Stamped","DataFormat","struct");
Rel_Velocity_Guidance_ROS = rospublisher("/chaser/gnc/guidance/relative/velocity","geometry_msgs/Vector3Stamped","DataFormat","struct");

% Attitude Topics
Chaser_DesiredAttitude_ROS = rospublisher("/chaser/gnc/attitude/desired","geometry_msgs/QuaternionStamped","DataFormat","struct");

% Simulation Clock topic
Simulation_Clock_ROS_sub = rossubscriber("/Simulation_Clock","std_msgs/Float64","DataFormat","struct");
Clock_ROS_sub = rossubscriber("/Clock","std_msgs/Time","DataFormat","struct");
% start GNC node topic
GNC_Run_ROS_sub = rossubscriber("/GNC_Run","std_msgs/Bool","DataFormat","struct");

%% Messages
msg = rosmessage("geometry_msgs/Vector3Stamped","DataFormat","struct");
msg_quat = rosmessage("geometry_msgs/QuaternionStamped","DataFormat","struct");
msg_float = rosmessage("std_msgs/Float64","DataFormat","struct");
msg_Float64MultiArray = rosmessage("std_msgs/Float64MultiArray","DataFormat","struct");
msg_UInt32MultiArray = rosmessage("std_msgs/UInt32MultiArray","DataFormat","struct");
msg_UInt32 = rosmessage("std_msgs/UInt32","DataFormat","struct");
msg_bool = rosmessage("std_msgs/Bool","DataFormat","struct");
msg_time = rosmessage("std_msgs/Time","DataFormat","struct");

%% Initialize publisher topics
t0 = uint32([0;0]);
% Control 
ROS_fcns.publish_vector2ros(Chaser_Force_ROS,msg,[0;0;0],t0); % commanded force
ROS_fcns.publish_vector2ros(Chaser_Torque_ROS,msg,[0;0;0],t0); % commanded torque
ROS_fcns.publish_vector2ros(Chaser_PositionError_ROS,msg,[0;0;0],t0); % position control error
ROS_fcns.publish_vector2ros(Chaser_VelocityError_ROS,msg,[0;0;0],t0); % velocity control error
ROS_fcns.publish_quat2ros(Chaser_AttitudeError_ROS,msg_quat,[0;0;0;0],t0); % Attitude control error

% Guidance
ROS_fcns.publish_quat2ros(Chaser_DesiredAttitude_ROS,msg_quat,[0;0;0;0],t0); % desired attitude
ROS_fcns.publish_vector2ros(Rel_Position_Guidance_ROS,msg,[0;0;0],t0); % Desired relative position
ROS_fcns.publish_vector2ros(Rel_Velocity_Guidance_ROS,msg,[0;0;0],t0); % Desired relative velocity

% Navigation
ROS_fcns.publish_vector2ros(Rel_Position_Est_ROS,msg,[0;0;0],t0); % estimated relative position
ROS_fcns.publish_vector2ros(Rel_Velocity_Est_ROS,msg,[0;0;0],t0); % estimated velocity position
ROS_fcns.publish_data2ros(Chaser_GPS_EKF_ROS,msg_Float64MultiArray,zeros(42,1)); % GPS EKF output
ROS_fcns.publish_data2ros(Chaser_Rel_EKF_ROS,msg_Float64MultiArray,zeros(42,1)); % Relative navigation EKF output

% Inertial state
ROS_fcns.publish_vector2ros(Chaser_Position_Est_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Chaser_Velocity_Est_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Target_Position_Est_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Target_Velocity_Est_ROS,msg,[0;0;0],t0);

ROS_fcns.publish_vector2ros(Chaser_Position_Est_Error_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Chaser_Velocity_Est_Error_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Target_Position_Est_Error_ROS,msg,[0;0;0],t0);
ROS_fcns.publish_vector2ros(Target_Velocity_Est_Error_ROS,msg,[0;0;0],t0);


%% GNC Initialization
StartGNC_Msg = GNC_Run_ROS_sub.LatestMessage;
StartNode = StartGNC_Msg.Data;
while ~StartNode
    % Check if this node need to be killed
    StartGNC_Msg = GNC_Run_ROS_sub.LatestMessage;
    StartNode = StartGNC_Msg.Data;
end

ChaserStates = [Chaser_Position_ROS_sub.LatestMessage.Vector.X;
    Chaser_Position_ROS_sub.LatestMessage.Vector.Y;
    Chaser_Position_ROS_sub.LatestMessage.Vector.Z;
    Chaser_Velocity_ROS_sub.LatestMessage.Vector.X;
    Chaser_Velocity_ROS_sub.LatestMessage.Vector.Y;
    Chaser_Velocity_ROS_sub.LatestMessage.Vector.Z];

TargetStates = [Target_Position_ROS_sub.LatestMessage.Vector.X;
    Target_Position_ROS_sub.LatestMessage.Vector.Y;
    Target_Position_ROS_sub.LatestMessage.Vector.Z;
    Target_Velocity_ROS_sub.LatestMessage.Vector.X;
    Target_Velocity_ROS_sub.LatestMessage.Vector.Y;
    Target_Velocity_ROS_sub.LatestMessage.Vector.Z];

CTL_Accel_ECI = [0;0;0];

%{
P0 = zeros(12,12);
P0(1:3,1:3)     = (1e-6).*eye(3,3);
P0(4:6,4:6)     = (1e-9).*eye(3,3);
P0(7:9,7:9)     = (1e-6).*eye(3,3);
P0(10:12,10:12) = (1e-9).*eye(3,3);

R0 = zeros(9,9);
R0(1:3,1:3) = (1e-12).*eye(3,3);
R0(4:6,4:6) = (1e-16).*eye(3,3);
R0(7:9,7:9) = (1e-19).*eye(3,3);


Q0 = zeros(12,12);
Q0 = 1000.*P0;

EKF_pre = [TargetStates;ChaserStates;P0(:)];
%}

%%{
P0 = zeros(6,6);
P0(1:3,1:3)     = (1e-6).*eye(3,3);
P0(4:6,4:6)     = (1e-9).*eye(3,3);
R0 = zeros(3,3);
R0(1:3,1:3) = (1e-12).*eye(3,3);

Q0 = zeros(6,6);
Q0 = 1000.*P0;

EKF_pre = [TargetStates;P0(:)];
EKF_post = EKF_pre;
%}

%%{
P0_GPS = zeros(6,6);
P0_GPS(1:3,1:3) = diag([1e-12 1e-12 1e-12]);
P0_GPS(4:6,4:6) = diag([1e-15 1e-15 1e-15]);
R0_GPS = zeros(6,6);
R0_GPS(1:3,1:3) = (1e0)*diag([1e-18 1e-18 1e-18]);
R0_GPS(4:6,4:6) = (1e0)*diag([1e-21 1e-21 1e-21]);

Q0_GPS = zeros(6,6);
Q0_GPS(1:3,1:3) = (1e-0)*diag([1e-9 1e-9 1e-9]);
Q0_GPS(4:6,4:6) = (1e-0)*diag([1e-12 1e-12 1e-12]);

EKF_GPS_pre = [ChaserStates;P0_GPS(:)];
EKF_GPS_post = EKF_GPS_pre;
%}

rate = rateControl(dt);
reset(rate);
while StartNode
    Node_Time = Simulation_Clock_ROS_sub.LatestMessage.Data;
    GNC_flags = [GNC_Nav_flag_sub.LatestMessage.Data;
        GNC_Ctl_flag_sub.LatestMessage.Data;
        GNC_Guidance_flag_sub.LatestMessage.Data];
    Hardware_flags = [Hardware_OBC_flag_sub.LatestMessage.Data;
        Hardware_GPSsim_flag_sub.LatestMessage.Data;
        Hardware_GPSrec_flag_sub.LatestMessage.Data];
    Sensor_flags = [Sensor_Vision_flag_ROS_sub.LatestMessage.Data;
        Sensor_RADAR_flag_ROS_sub.LatestMessage.Data;
        Sensor_TLE_flag_ROS_sub.LatestMessage.Data;
        Sensor_GPS_flag_ROS_sub.LatestMessage.Data];
    %% States
    time = [Clock_ROS_sub.LatestMessage.Data.Sec;Clock_ROS_sub.LatestMessage.Data.Nsec];

    ChaserStates = [Chaser_Position_ROS_sub.LatestMessage.Vector.X;
        Chaser_Position_ROS_sub.LatestMessage.Vector.Y;
        Chaser_Position_ROS_sub.LatestMessage.Vector.Z;
        Chaser_Velocity_ROS_sub.LatestMessage.Vector.X;
        Chaser_Velocity_ROS_sub.LatestMessage.Vector.Y;
        Chaser_Velocity_ROS_sub.LatestMessage.Vector.Z];
    

    ChaserAttitude = [Chaser_Attitude_ROS_sub.LatestMessage.Quaternion.X;
        Chaser_Attitude_ROS_sub.LatestMessage.Quaternion.Y;
        Chaser_Attitude_ROS_sub.LatestMessage.Quaternion.Z;
        Chaser_Attitude_ROS_sub.LatestMessage.Quaternion.W;
        Chaser_AngRates_ROS_sub.LatestMessage.Vector.X;
        Chaser_AngRates_ROS_sub.LatestMessage.Vector.Y;
        Chaser_AngRates_ROS_sub.LatestMessage.Vector.Z];

    TargetStates = [Target_Position_ROS_sub.LatestMessage.Vector.X;
        Target_Position_ROS_sub.LatestMessage.Vector.Y;
        Target_Position_ROS_sub.LatestMessage.Vector.Z;
        Target_Velocity_ROS_sub.LatestMessage.Vector.X;
        Target_Velocity_ROS_sub.LatestMessage.Vector.Y;
        Target_Velocity_ROS_sub.LatestMessage.Vector.Z];
    

    TargetAttitude = [Target_Attitude_ROS_sub.LatestMessage.Quaternion.X;
        Target_Attitude_ROS_sub.LatestMessage.Quaternion.Y;
        Target_Attitude_ROS_sub.LatestMessage.Quaternion.Z;
        Target_Attitude_ROS_sub.LatestMessage.Quaternion.W;
        Target_AngRates_ROS_sub.LatestMessage.Vector.X;
        Target_AngRates_ROS_sub.LatestMessage.Vector.Y;
        Target_AngRates_ROS_sub.LatestMessage.Vector.Z];
    
    %% Sensors
    Chaser_TLE_OE   = Chaser_TLE_OE_ROS_sub.LatestMessage.Data;
    Chaser_TLE_Time = Chaser_TLE_time_ROS_sub.LatestMessage.Data;
    Chaser_TLE_flag = Chaser_TLE_flag_ROS_sub.LatestMessage.Data;
    [Chaser_TLE_Position,Chaser_TLE_Velocity] = Rotations.OE2ECI([Chaser_TLE_OE(1:5);Chaser_TLE_OE(7)], ...
        ConstantParameters.mu_Earth);


    Chaser_Target_TLE_OE   = Chaser_TLE_OE_ROS_sub.LatestMessage.Data;
    Chaser_Target_TLE_Time = Chaser_TLE_time_ROS_sub.LatestMessage.Data;
    Chaser_Target_TLE_flag = Chaser_TLE_flag_ROS_sub.LatestMessage.Data;
    
    Chaser_GPS_Position     = [Chaser_GPS_Position_ROS_sub.LatestMessage.Vector.X;
        Chaser_GPS_Position_ROS_sub.LatestMessage.Vector.Y;
        Chaser_GPS_Position_ROS_sub.LatestMessage.Vector.Z];
    Chaser_GPS_Velocity     = [Chaser_GPS_Velocity_ROS_sub.LatestMessage.Vector.X;
        Chaser_GPS_Velocity_ROS_sub.LatestMessage.Vector.Y;
        Chaser_GPS_Velocity_ROS_sub.LatestMessage.Vector.Z];
    Chaser_GPS_Acceleration = [Chaser_GPS_Acceleration_ROS_sub.LatestMessage.Vector.X;
        Chaser_GPS_Acceleration_ROS_sub.LatestMessage.Vector.Y;
        Chaser_GPS_Acceleration_ROS_sub.LatestMessage.Vector.Z];
    Chaser_GPS_Time         = Chaser_GPS_Time_ROS_sub.LatestMessage.Data;
    Chaser_GPS_Status       = Chaser_GPS_Status_ROS_sub.LatestMessage.Data;

    RADAR_Measurements = [Chaser_RADAR_ROS_sub.LatestMessage.Vector.X;
        Chaser_RADAR_ROS_sub.LatestMessage.Vector.Y;
        Chaser_RADAR_ROS_sub.LatestMessage.Vector.Z];

    Vision_Measurements = [Chaser_Vision_ROS_sub.LatestMessage.Vector.X;
        Chaser_Vision_ROS_sub.LatestMessage.Vector.Y;
        Chaser_Vision_ROS_sub.LatestMessage.Vector.Z];

    %% Navigation
    ChaserStates_Est = ChaserStates;
    TargetStates_Est = TargetStates;
    if GNC_flags(1)
        %{
        [TargetStates_Est,ChaserStates_Est,EKF_post] = Navigation.EKF_RADAR.estimator(EKF_pre, CTL_Accel_ECI, ...
            RADAR_Measurements,ChaserStates, true, ...
            [Chaser_TLE_Position;Chaser_TLE_Velocity], Chaser_TLE_flag, dt, Node_Time, ...
            Q0, R0, ConstantParameters);
        %}
        if (Sensor_flags(4) && Hardware_flags(2) && Hardware_flags(3)) || Sensor_flags(3)
            [ChaserStates_Est,EKF_GPS_post] = Navigation.EKF_GPS.estimator(EKF_GPS_pre,CTL_Accel_ECI, ...
            [Chaser_GPS_Position;Chaser_GPS_Velocity], Chaser_GPS_Status, [Chaser_TLE_Position;Chaser_TLE_Velocity], Chaser_TLE_flag, ...
            dt, Node_Time, Q0_GPS, R0_GPS, ConstantParameters);
            EKF_GPS_pre = EKF_GPS_post;
            
            if ~Chaser_GPS_Status && ~Chaser_TLE_flag % issues between GPS signal fix and chaser inertial state estimator
                ChaserStates_Est = ChaserStates;
            end
        end
        if Sensor_flags(2)
            %%{
            [TargetStates_Est,EKF_post] = Navigation.EKF_RADAR_Reduced.estimator(EKF_pre, RADAR_Measurements, ...
            ChaserStates_Est, dt, Node_Time, Q0, R0, ConstantParameters);
            %}
            EKF_pre = EKF_post;
        end
    end

    TargetStates_Est_Error = TargetStates_Est - TargetStates;
    ChaserStates_Est_Error = ChaserStates_Est - ChaserStates;

    C_HI  =  Rotations.CHI(TargetStates_Est);
    RelPosition_Nav = C_HI*(ChaserStates_Est(1:3) - TargetStates_Est(1:3));
    rTarget = sqrt(TargetStates_Est(1)^2 + TargetStates_Est(2)^2 + TargetStates_Est(3)^2);
    w_HI = skew_matrix(TargetStates_Est(1:3))*TargetStates_Est(4:6)/(rTarget^2);
    RelVelocity_Nav = C_HI*(ChaserStates_Est(4:6) - TargetStates_Est(4:6)) - (skew_matrix(w_HI)*RelPosition_Nav);
    
    %% Guidance
    % Desired Position/Velocity
    RelPosition_Desired = [0;1;0];
    RelVelocity_Desired = [0;0;0];

    % Desired Attitude
    RelPosition_Nav_ECI = C_HI'*RelPosition_Nav;
    RelPosition_UnitVector = -RelPosition_Nav_ECI/sqrt(RelPosition_Nav_ECI(1)^2 + RelPosition_Nav_ECI(2)^2 + RelPosition_Nav_ECI(3)^2);
    alpha = atan2(RelPosition_UnitVector(2),RelPosition_UnitVector(1));
    beta = asin(RelPosition_UnitVector(3));
    C = Rotations.Cy(beta)*Rotations.Cz(alpha);

    x = RelPosition_UnitVector;
    y = C'*Iy; 
    z = cross(x,y);

    C_BI =  [dot(x,Ix) dot(x,Iy) dot(x,Iz); ... 
             dot(y,Ix) dot(y,Iy) dot(y,Iz); ... 
             dot(z,Ix) dot(z,Iy) dot(z,Iz)];
 
    
    quaternion_desired = Rotations.rotm2quat(C_BI);
    quaternion_desired = Rotations.NormalizeQuaternion(quaternion_desired); % Normalize and ensure q(4) is positive

    %% Errors
    Translation_error = [RelPosition_Desired - RelPosition_Nav;
        RelVelocity_Desired - RelVelocity_Nav];
    quaternion_error  = dynamics.Attitude.quat_error(ChaserAttitude(1:4),quaternion_desired);

    %% Controller
    if GNC_flags(2)
        CTL_Accel = K_lqr*Translation_error;
        CTL_Accel_ECI = C_HI'*CTL_Accel;
        Force = m.*CTL_Accel;
        Torque = (-Kp_Attitude*inertiaMatrix_Chaser*quaternion_error(1:3))+(-Kd_Attitude*inertiaMatrix_Chaser*ChaserAttitude(5:7))-(cross(ChaserAttitude(5:7),inertiaMatrix_Chaser*(ChaserAttitude(5:7)))); 
    else
        Force = [0;0;0];
        Torque = [0;0;0];
    end

    %% Publish to topics
    % Control 
    ROS_fcns.publish_vector2ros(Chaser_Force_ROS,msg,Force,time); % commanded force
    ROS_fcns.publish_vector2ros(Chaser_Torque_ROS,msg,Torque,time); % commanded torque
    ROS_fcns.publish_vector2ros(Chaser_PositionError_ROS,msg,Translation_error(1:3),time); % position control error
    ROS_fcns.publish_vector2ros(Chaser_VelocityError_ROS,msg,Translation_error(4:6),time); % velocity control error
    ROS_fcns.publish_quat2ros(Chaser_AttitudeError_ROS,msg_quat,quaternion_error,time); % Attitude control error

    % Guidance
    ROS_fcns.publish_quat2ros(Chaser_DesiredAttitude_ROS,msg_quat,quaternion_desired,time); % desired attitude
    ROS_fcns.publish_vector2ros(Rel_Position_Guidance_ROS,msg,RelPosition_Desired,time); % Desired relative position
    ROS_fcns.publish_vector2ros(Rel_Velocity_Guidance_ROS,msg,RelVelocity_Desired,time); % Desired relative velocity

    % Navigation
    ROS_fcns.publish_vector2ros(Rel_Position_Est_ROS,msg,RelPosition_Nav,time); % estimated relative position
    ROS_fcns.publish_vector2ros(Rel_Velocity_Est_ROS,msg,RelVelocity_Nav,time); % estimated velocity position
    ROS_fcns.publish_data2ros(Chaser_GPS_EKF_ROS,msg_Float64MultiArray,EKF_GPS_post); % GPS EKF output
    ROS_fcns.publish_data2ros(Chaser_Rel_EKF_ROS,msg_Float64MultiArray,EKF_post); % Relative navigation EKF output

    % Inertial state
    ROS_fcns.publish_vector2ros(Chaser_Position_Est_ROS,msg,ChaserStates_Est(1:3),time);
    ROS_fcns.publish_vector2ros(Chaser_Velocity_Est_ROS,msg,ChaserStates_Est(4:6),time);
    ROS_fcns.publish_vector2ros(Target_Position_Est_ROS,msg,TargetStates_Est(1:3),time);
    ROS_fcns.publish_vector2ros(Target_Velocity_Est_ROS,msg,TargetStates_Est(4:6),time);

    ROS_fcns.publish_vector2ros(Chaser_Position_Est_Error_ROS,msg,ChaserStates_Est_Error(1:3),time);
    ROS_fcns.publish_vector2ros(Chaser_Velocity_Est_Error_ROS,msg,ChaserStates_Est_Error(4:6),time);
    ROS_fcns.publish_vector2ros(Target_Position_Est_Error_ROS,msg,TargetStates_Est_Error(1:3),time);
    ROS_fcns.publish_vector2ros(Target_Velocity_Est_Error_ROS,msg,TargetStates_Est_Error(4:6),time);

    %% Check if this node need to be killed
    StartGNC_Msg = GNC_Run_ROS_sub.LatestMessage;
    if ~isempty(StartGNC_Msg.Data)
        StartNode = StartGNC_Msg.Data;
    end
    waitfor(rate);
end