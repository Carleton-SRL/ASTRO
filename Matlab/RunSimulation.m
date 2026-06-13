%{
© 2025 Yazan Chihabi
%}

%% Starts the simulation
disp('Simulation in progress...')
% if hardware_flags(2)
%     flush(GPS_SimulatorObj);
% end
% if hardware_flags(3)
%     flush(gpsObj);
% end
ts = tic;
%% Performance/runtime options
if ~exist('SimulationOptions','var')
    SimulationOptions = struct();
end
if ~isfield(SimulationOptions,'use_fixed_step_propagator'), SimulationOptions.use_fixed_step_propagator = true; end
if ~isfield(SimulationOptions,'ros_publish_skip'), SimulationOptions.ros_publish_skip = 1; end
if ~isfield(SimulationOptions,'low_rate_ros_publish_skip'), SimulationOptions.low_rate_ros_publish_skip = max(1,SimulationOptions.ros_publish_skip); end
if ~isfield(SimulationOptions,'realtime_mode'), SimulationOptions.realtime_mode = true; end
if ~isfield(SimulationOptions,'realtime_time_scale'), SimulationOptions.realtime_time_scale = 1.0; end  % 1.0 = real time; 2.0 = 2x faster than real time
if ~isfield(SimulationOptions,'realtime_max_overrun_warnings'), SimulationOptions.realtime_max_overrun_warnings = 20; end
if ~isfield(SimulationOptions,'verbose_timing'), SimulationOptions.verbose_timing = false; end
if ~isfield(SimulationOptions,'publish_clock_every_step'), SimulationOptions.publish_clock_every_step = true; end
if ~isfield(SimulationOptions,'show_simulation_clock'), SimulationOptions.show_simulation_clock = false; end
if ~isfield(SimulationOptions,'clock_display_period'), SimulationOptions.clock_display_period = 1.0; end
if ~isfield(SimulationOptions,'clock_display_wall_ratio'), SimulationOptions.clock_display_wall_ratio = true; end
if ~isfield(SimulationOptions,'publish_ros'), SimulationOptions.publish_ros = true; end
if ~isfield(SimulationOptions,'enable_gazebo_visualizer'), SimulationOptions.enable_gazebo_visualizer = false; end
if ~isfield(SimulationOptions,'gazebo_publish_skip'), SimulationOptions.gazebo_publish_skip = 1; end
if ~isfield(SimulationOptions,'gazebo_publish_celestials'), SimulationOptions.gazebo_publish_celestials = true; end
if ~isfield(SimulationOptions,'gps_compatible_propagation'), SimulationOptions.gps_compatible_propagation = hardware_flags(2); end
if ~isfield(SimulationOptions,'max_propagation_step'), SimulationOptions.max_propagation_step = dt_GPS; end
% Backward-compatible alias: if the user set SimulationOptions.realtime, respect it.
if isfield(SimulationOptions,'realtime') && ~isfield(SimulationOptions,'realtime_mode')
    SimulationOptions.realtime_mode = logical(SimulationOptions.realtime);
end

SimulationOptions.publish_ros = logical(SimulationOptions.publish_ros);
if isinf(SimulationOptions.ros_publish_skip)
    SimulationOptions.ros_publish_skip = realmax;
else
    SimulationOptions.ros_publish_skip = max(1,round(SimulationOptions.ros_publish_skip));
end
if isinf(SimulationOptions.low_rate_ros_publish_skip)
    SimulationOptions.low_rate_ros_publish_skip = realmax;
else
    SimulationOptions.low_rate_ros_publish_skip = max(1,round(SimulationOptions.low_rate_ros_publish_skip));
end
if isinf(SimulationOptions.gazebo_publish_skip)
    SimulationOptions.gazebo_publish_skip = realmax;
else
    SimulationOptions.gazebo_publish_skip = max(1,round(SimulationOptions.gazebo_publish_skip));
end
SimulationOptions.realtime_time_scale = max(eps,SimulationOptions.realtime_time_scale);
SimulationOptions.clock_display_period = max(0.1,SimulationOptions.clock_display_period);
SimulationOptions.max_propagation_step = max(eps,SimulationOptions.max_propagation_step);

% One switch to hard-disable all ROS publication paths without having to edit
% hardware_flags everywhere. This is important for offline speed tests.
rosEnabled = hardware_flags(1) && SimulationOptions.publish_ros;
gazeboVizEnabled = SimulationOptions.enable_gazebo_visualizer && exist('GazeboVizPublishers','var') && ~isempty(GazeboVizPublishers);

SimulationTiming.propagation_sec = 0;
SimulationTiming.ros_publish_sec = 0;
SimulationTiming.sensor_sec = 0;
SimulationTiming.step_sec = zeros(1,length(t));
SimulationTiming.slack_sec = zeros(1,length(t));
SimulationTiming.overrun_sec = zeros(1,length(t));
SimulationTiming.overrun_count = 0;
SimulationTiming.max_overrun_sec = 0;
SimulationTiming.mean_step_sec = 0;

% Efficient terminal clock state. This updates one command-window line at a
% low rate instead of printing every step, which avoids slowing real-time/HIL runs.
ClockDisplayState.last_update_sim_time = -inf;
ClockDisplayState.last_line_length = 0;
ClockDisplayState.enabled = logical(SimulationOptions.show_simulation_clock);

if hardware_flags(2)
    [GPS_Pos,GPS_Vel,Status_Receiver,GPS_week_Receiver,GPS_Time_Receiver,GPS_Time_Status] = GPS_Receiver.parserBESTXYZ(gpsObj.UserData);
end

k = 1;
tpre = 0;
ChaserAppliedAccel = [0;0;0];
ChaserAppliedTorque = [0;0;0];
ChaserGPS = [r2_I_prop;v2_I_prop;a2_I_prop];
ChaserGPS_prev = ChaserGPS;
if rosEnabled
    ROS_fcns.publish_data2ros(GNC_Run_ROS,msg_bool,true);
end

for i = 2:length(t)+1
    step_tic = tic;
    targetWallTime = t(i-1) / SimulationOptions.realtime_time_scale;

    % Propagation grid selection:
    % - GPS/HIL mode uses the original fine dt_GPS grid for compatibility.
    % - Fast offline mode uses a coarser grid, often [0 dt], to avoid doing
    %   50 RK4 substeps per one-second simulation step when GPS sim is off.
    if hardware_flags(2) || SimulationOptions.gps_compatible_propagation
        tpropStep = tpropGPS;
    else
        if SimulationOptions.max_propagation_step >= dt_data
            tpropStep = [0 dt_data];
        else
            tpropStep = 0:SimulationOptions.max_propagation_step:dt_data;
            if tpropStep(end) < dt_data
                tpropStep = [tpropStep dt_data];
            end
        end
    end
    tpropStep_length = length(tpropStep);
    forceScale = max(1,tpropStep_length-1);

    rosPublishThisStep = rosEnabled && (mod(i-2,SimulationOptions.ros_publish_skip) == 0);
    rosLowRatePublishThisStep = rosEnabled && (mod(i-2,SimulationOptions.low_rate_ros_publish_skip) == 0);
    gazeboPublishThisStep = gazeboVizEnabled && (mod(i-2,SimulationOptions.gazebo_publish_skip) == 0);

    if rosLowRatePublishThisStep
        %% ROS Flags
        ROS_fcns.publish_data2ros(GNC_Nav_flag,msg_bool,GNC_flags(1));
        ROS_fcns.publish_data2ros(GNC_Ctl_flag,msg_bool,GNC_flags(2));
        ROS_fcns.publish_data2ros(GNC_Guidance_flag,msg_bool,GNC_flags(3));
        ROS_fcns.publish_data2ros(Sensor_Vision_flag_ROS,msg_bool,Sensor_flags(1));
        ROS_fcns.publish_data2ros(Sensor_RADAR_flag_ROS,msg_bool,Sensor_flags(2));
        ROS_fcns.publish_data2ros(Sensor_TLE_flag_ROS,msg_bool,Sensor_flags(3));
        ROS_fcns.publish_data2ros(Sensor_GPS_flag_ROS,msg_bool,Sensor_flags(4));
        ROS_fcns.publish_data2ros(Hardware_OBC_flag,msg_bool,hardware_flags(1));
        ROS_fcns.publish_data2ros(Hardware_GPSsim_flag,msg_bool,hardware_flags(2));
        ROS_fcns.publish_data2ros(Hardware_GPSrec_flag,msg_bool,hardware_flags(3));
    end

    %% Read GPS Receiver
    if hardware_flags(3)
        [GPS_Pos,GPS_Vel,Status_Receiver,GPS_week_Receiver,GPS_Time_Receiver,GPS_Time_Status] = GPS_Receiver.parserBESTXYZ(gpsObj.UserData);
        
        if Status_Receiver
            % [StateVars_Chaser_GPS_Receiver(1:3,i-1), StateVars_Chaser_GPS_Receiver(4:6,i-1)] = ecef2eci(invjday(JD), GPS_Pos(1:3), GPS_Vel(1:3));
            [StateVars_Chaser_GPS_Receiver(1:3,i-1), StateVars_Chaser_GPS_Receiver(4:6,i-1),~] = Rotations.ECEF2ECI(MJD_UTC, ...
                [GPS_Pos(1:3); GPS_Vel(1:3);0;0;0], ConstantParameters, eopdata);
            ChaserGPS = [StateVars_Chaser_GPS_Receiver(1:3,i-1); StateVars_Chaser_GPS_Receiver(4:6,i-1);
                (StateVars_Chaser_GPS_Receiver(4:6,i-1)-ChaserGPS_prev(4:6))/dt];
            ChaserGPS_prev = ChaserGPS;
        else
            ChaserGPS = [r2_I_prop;v2_I_prop;(v2_I_prop-ChaserGPS_prev(4:6))/dt];
            ChaserGPS_prev = ChaserGPS;
        end
        GPS_Receiver_Status(i-1) = Status_Receiver;
        GPS_TimeStamps_Receiver(:,i-1) = [GPS_week_Receiver;GPS_Time_Receiver];
        
        if rosPublishThisStep
            ROS_fcns.publish_vector2ros(Chaser_GPS_Position_ROS,msg,ChaserGPS(1:3),ROS_time);
            ROS_fcns.publish_vector2ros(Chaser_GPS_Velocity_ROS,msg,ChaserGPS(4:6),ROS_time);
            ROS_fcns.publish_vector2ros(Chaser_GPS_Acceleration_ROS,msg,ChaserGPS(7:9),ROS_time);
            ROS_fcns.publish_data2ros(Chaser_GPS_Time_ROS,msg_UInt32MultiArray, ...
                uint32(GPS_TimeStamps_Receiver(:,i-1)));
            ROS_fcns.publish_data2ros(Chaser_GPS_Status_ROS,msg_bool,Status_Receiver);
        end
    end
    if rosPublishThisStep
        ROS_fcns.publish_vector2ros(Chaser_Position_ROS,msg,r2_I_prop,ROS_time);
        ROS_fcns.publish_vector2ros(Chaser_Velocity_ROS,msg,v2_I_prop,ROS_time);
        ROS_fcns.publish_vector2ros(Chaser_AngRates_ROS,msg,Chaser_AngularVelocity_prop,ROS_time);
        ROS_fcns.publish_quat2ros(Chaser_Attitude_ROS,msg_quat, ...
            Rotations.NormalizeQuaternion(Chaser_Attitude_prop),ROS_time);

        ROS_fcns.publish_vector2ros(Target_Position_ROS,msg,r1_I_prop,ROS_time);
        ROS_fcns.publish_vector2ros(Target_Velocity_ROS,msg,v1_I_prop,ROS_time);
        ROS_fcns.publish_vector2ros(Target_AngRates_ROS,msg,Target_AngularVelocity_prop,ROS_time);
        ROS_fcns.publish_quat2ros(Target_Attitude_ROS,msg_quat, ...
            Rotations.NormalizeQuaternion(Target_Attitude_prop),ROS_time);
    end

    %% Standalone Gazebo visualization state publication
    % Publishes inertial [pos; vel; quat; omega] as nav_msgs/Odometry.
    % This is intentionally independent of hardware_flags(1)/OBC ROS so the
    % visualizer can run while the GNC/ROS deployment interface remains off.
    if gazeboPublishThisStep
        try
            targetGazeboState = [r1_I_prop; v1_I_prop; ...
                Rotations.NormalizeQuaternion(Target_Attitude_prop); ...
                Target_AngularVelocity_prop];
            chaserGazeboState = [r2_I_prop; v2_I_prop; ...
                Rotations.NormalizeQuaternion(Chaser_Attitude_prop); ...
                Chaser_AngularVelocity_prop];
            GazeboViz.publishInertialState(GazeboVizPublishers.target, ...
                targetGazeboState, GazeboVizPublishers.frame_id, ...
                GazeboVizPublishers.child_target, GazeboVizPublishers.quaternion_order);
            GazeboViz.publishInertialState(GazeboVizPublishers.chaser, ...
                chaserGazeboState, GazeboVizPublishers.frame_id, ...
                GazeboVizPublishers.child_chaser, GazeboVizPublishers.quaternion_order);
            if isfield(SimulationOptions,'gazebo_publish_celestials') && SimulationOptions.gazebo_publish_celestials
                if exist('MJD_UTC0','var') && exist('ConstantParameters','var') && ...
                        exist('eopdata','var') && exist('PC','var') && exist('centralbody','var')
                    publish_gazebo_ephemeris_bodies(GazeboVizPublishers, t(i-1), ...
                        MJD_UTC0, centralbody, ConstantParameters, eopdata, PC);
                end
            end

        catch ME
            warning('Gazebo visualizer publish failed at step %d: %s', i, ME.message);
            gazeboVizEnabled = false;
        end
    end

    %% Vision Sensor Modelling
    if Sensor_flags(1)
        [range_chaser2target,angle_chaser2target] = SensorModels.LOS.Model([r1_I_prop; v1_I_prop], ...
            [r2_I_prop; v2_I_prop],LOS_std);
        if rosPublishThisStep
            ROS_fcns.publish_vector2ros(Chaser_Vision_ROS,msg, ...
                [range_chaser2target;angle_chaser2target] ,ROS_time);
        end
    end
    %% RADAR Sensor Modelling
    if Sensor_flags(2)
        [range_chaser2target_RADAR,angle_chaser2target_RADAR] = SensorModels.RADAR.Model([r1_I_prop; v1_I_prop], ...
            [r2_I_prop; v2_I_prop],RADAR_params,ConstantParameters);
        if rosPublishThisStep
            ROS_fcns.publish_vector2ros(Chaser_RADAR_ROS,msg, ...
                [range_chaser2target_RADAR;angle_chaser2target_RADAR] ,ROS_time);
        end
    end

    %% TLE Modelling
    if Sensor_flags(3)
        TLEflag = floor(t(i-1)/TLE_update_rate) - floor(tpre/TLE_update_rate);
        if TLEflag == 1
            TLE_prop_target = SensorModels.TLE.Model([r1_I_prop;v1_I_prop],BSRP_t,Bdrag_t,mu,TLE_std);
            TLE_prop = SensorModels.TLE.Model([r2_I_prop;v2_I_prop],BSRP_c,Bdrag_c,mu,TLE_std);
            TLE_update = true;
            if rosEnabled
                ROS_fcns.publish_data2ros(Chaser_TLE_OE_ROS,msg_Float64MultiArray,TLE_prop);
                ROS_fcns.publish_data2ros(Chaser_TLE_time_ROS,msg_UInt32MultiArray, ...
                    uint32(datevec(datetime([1970 1 1 0 0 posix_time_prop]))));
                ROS_fcns.publish_data2ros(Chaser_TLE_flag_ROS,msg_bool,TLE_update);

                ROS_fcns.publish_data2ros(Chaser_Target_TLE_OE_ROS,msg_Float64MultiArray,TLE_prop_target);
                ROS_fcns.publish_data2ros(Chaser_Target_TLE_time_ROS,msg_UInt32MultiArray, ...
                    uint32(datevec(datetime([1970 1 1 0 0 posix_time_prop]))));
                ROS_fcns.publish_data2ros(Chaser_Target_TLE_flag_ROS,msg_bool,TLE_update);
            end
        else
            TLE_update = false;
            if rosEnabled
                ROS_fcns.publish_data2ros(Chaser_TLE_flag_ROS,msg_bool,TLE_update);
                ROS_fcns.publish_data2ros(Chaser_Target_TLE_flag_ROS,msg_bool,TLE_update);
            end
        end
    end
    
    %% Sun & Moon Models
    if rosLowRatePublishThisStep
        ROS_fcns.publish_data2ros(Sun_OE_ROS,msg_Float64MultiArray,[oe_sun(:,i-1);tanos(i-1)]);
        ROS_fcns.publish_data2ros(Moon_OE_ROS,msg_Float64MultiArray,[oe_moon(:,i-1);tanom(i-1)]);
    end

    %% Navigation
    %{
    if GNC_flags(1)
        [data_DUKF,dataParam_DUKF,k,QKF,RKF,QP,RP,Storage,qdot,q,ChaserStates,TargetStates,F_out, NavOut] = Navigation.DUKF.Nav(data_DUKF,dataParam_DUKF, ...
            k,QKF,RKF,QP,RP,Storage,t(i-1), dt,ChaserAppliedAccel, angle_chaser2target,params, range_chaser2target, tanom, tanos, oe_moon, oe_sun, ...
            thetaGMTini,nmax, mmax, Cnm, Snm, GravityFactorial, GravityBinomial, AuxilaryParameters, ...
            ConstantParameters, Q_adapt_flag, R_adapt_flag,  N_window, UKFParams, ChaserGPS, Status_Receiver);
        RelativeStates_est(:,i-1) = [q;qdot];
        TargetStates_est(:,i-1) = TargetStates;
        ChaserStates_est(:,i-1) = ChaserStates;
        NavOut_sim(:,i-1) = NavOut;
        
    end
    %}
    %% Guidance, Navigation, and Control
    if rosEnabled
        % Keep the simulation clock at the base simulation rate in real-time/HIL mode.
        % Other high-bandwidth telemetry can still be throttled with ros_publish_skip.
        if SimulationOptions.publish_clock_every_step || rosPublishThisStep
            ROS_fcns.publish_data2ros(Simulation_Clock_ROS,msg_float,t(i-1));
        end
        ChaserForce = [Chaser_Force_ROS_sub.LatestMessage.Vector.X;
            Chaser_Force_ROS_sub.LatestMessage.Vector.Y;
            Chaser_Force_ROS_sub.LatestMessage.Vector.Z];
        CHI_Target = Rotations.CHI([r1_I_prop;v1_I_prop]);
        ChaserAppliedAccel = CHI_Target'*ChaserForce./m2;
        ChaserAppliedTorque = [Chaser_Torque_ROS_sub.LatestMessage.Vector.X;
            Chaser_Torque_ROS_sub.LatestMessage.Vector.Y;
            Chaser_Torque_ROS_sub.LatestMessage.Vector.Z];
        Control_Chaser(:,i-1) = [ChaserAppliedAccel;ChaserAppliedTorque];
        ChaserAttitude_Desired(:,i-1) = [Chaser_DesiredAttitude_ROS_sub.LatestMessage.Quaternion.X;
            Chaser_DesiredAttitude_ROS_sub.LatestMessage.Quaternion.Y;
            Chaser_DesiredAttitude_ROS_sub.LatestMessage.Quaternion.Z;
            Chaser_DesiredAttitude_ROS_sub.LatestMessage.Quaternion.W];
        ChaserAttitude_Error(:,i-1) = [Chaser_AttitudeError_ROS_sub.LatestMessage.Quaternion.X;
            Chaser_AttitudeError_ROS_sub.LatestMessage.Quaternion.Y;
            Chaser_AttitudeError_ROS_sub.LatestMessage.Quaternion.Z;
            Chaser_AttitudeError_ROS_sub.LatestMessage.Quaternion.W];
        RelativeStates_guidance(:,i-1) = [Rel_Position_Guidance_ROS_sub.LatestMessage.Vector.X;
            Rel_Position_Guidance_ROS_sub.LatestMessage.Vector.Y;
            Rel_Position_Guidance_ROS_sub.LatestMessage.Vector.Z;
            Rel_Velocity_Guidance_ROS_sub.LatestMessage.Vector.X;
            Rel_Velocity_Guidance_ROS_sub.LatestMessage.Vector.Y;
            Rel_Velocity_Guidance_ROS_sub.LatestMessage.Vector.Z];
        RelativeStates_est(:,i-1) = [Rel_Position_Est_ROS.LatestMessage.Vector.X;
            Rel_Position_Est_ROS.LatestMessage.Vector.Y;
            Rel_Position_Est_ROS.LatestMessage.Vector.Z;
            Rel_Velocity_Est_ROS.LatestMessage.Vector.X;
            Rel_Velocity_Est_ROS.LatestMessage.Vector.Y;
            Rel_Velocity_Est_ROS.LatestMessage.Vector.Z];
        TargetStates_est(:,i-1) = [Target_Position_Est_ROS.LatestMessage.Vector.X;
            Target_Position_Est_ROS.LatestMessage.Vector.Y;
            Target_Position_Est_ROS.LatestMessage.Vector.Z;
            Target_Velocity_Est_ROS.LatestMessage.Vector.X;
            Target_Velocity_Est_ROS.LatestMessage.Vector.Y;
            Target_Velocity_Est_ROS.LatestMessage.Vector.Z];
        ChaserStates_est(:,i-1) = [Chaser_Position_Est_ROS.LatestMessage.Vector.X;
            Chaser_Position_Est_ROS.LatestMessage.Vector.Y;
            Chaser_Position_Est_ROS.LatestMessage.Vector.Z;
            Chaser_Velocity_Est_ROS.LatestMessage.Vector.X;
            Chaser_Velocity_Est_ROS.LatestMessage.Vector.Y;
            Chaser_Velocity_Est_ROS.LatestMessage.Vector.Z];
        Chaser_Rel_EKF(:,i-1) = Chaser_Rel_EKF_ROS_sub.LatestMessage.Data;
        Chaser_GPS_EKF(:,i-1) = Chaser_GPS_EKF_ROS_sub.LatestMessage.Data;
    end
    
    %% Propagate
    % Propagate Target Spacecraft
    if hardware_flags(2)
        GPS_TimeStamps_Simulator(:,i-1) = [GPS_week;GPS_time];
    end
    
    StateVars_Chaser(:,i-1) = [r2_I_prop;v2_I_prop];
    StateVars_Target(:,i-1) = [r1_I_prop;v1_I_prop];

    propagation_tic = tic;
    if SimulationOptions.use_fixed_step_propagator
        % Propagate Target Spacecraft with fixed-step RK4 over tpropStep.
        flag_sc = 1;
        targetFcn = @(tau,states) dynamics.simulator(tau,states, Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody, eopdata, ...
            PC, flag_sc, [0;0;0]);
        targetstates = dynamics.propagate_fixed_step(tpropStep,[r1_I_prop; v1_I_prop],targetFcn);

        targetAttFcn = @(tau,states) dynamics.Attitude.simulator(tau,states,[0;0;0], ...
            [0;0;0], [0;0;0], inertiaMatrix_Target, inertiaMatrix_Target_inv);
        targetattitude = dynamics.propagate_fixed_step(tpropStep, ...
            [Target_Attitude_prop; Target_AngularVelocity_prop],targetAttFcn);

        r1_I_prop = targetstates(1:3,end);
        v1_I_prop = targetstates(4:6,end);
        Target_Attitude_prop = Rotations.NormalizeQuaternion(targetattitude(1:4,end));
        Target_AngularVelocity_prop = targetattitude(5:7,end);

        % Propagate Chaser attitude with fixed-step RK4.
        chaserAttFcn = @(tau,states) dynamics.Attitude.simulator(tau,states,ChaserAppliedTorque./forceScale, ...
            [0;0;0], [0;0;0], inertiaMatrix_Chaser, inertiaMatrix_Chaser_inv);
        chaserattitude = dynamics.propagate_fixed_step(tpropStep, ...
            [Chaser_Attitude_prop; Chaser_AngularVelocity_prop],chaserAttFcn);
        Chaser_Attitude_prop = Rotations.NormalizeQuaternion(chaserattitude(1:4,end));
        Chaser_AngularVelocity_prop = chaserattitude(5:7,end);

        % Propagate Chaser translational state. Keep the original dt/dt_data
        % outer subdivision behavior for GPS-simulator compatibility.
        nDataSteps = max(1,round(dt/dt_data));
        for j = 1:nDataSteps
            flag_sc = 2;
            chaserFcn = @(tau,states) dynamics.simulator(tau,states, Cnm, Snm, ...
                ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody, eopdata, ...
                PC, flag_sc, ChaserAppliedAccel./forceScale);
            chaserstates = dynamics.propagate_fixed_step(tpropStep,[r2_I_prop; v2_I_prop],chaserFcn);
            r2_I_prop = chaserstates(1:3,end);
            v2_I_prop = chaserstates(4:6,end);

            if dt_GPS/dt_data == 1
                chaserstates = [chaserstates(:,1),chaserstates(:,end)];
            end

            % Set and send the chaser spacecraft's position in the GPS simulator.
            if hardware_flags(2)
                [~,a2_E_prop_prev,GPS_week,GPS_time,thetaGMT,MJD_UTC,JD,GPS_Simulator_Clock] = GPS_Simulator.SetSpacecraftPosition_GPSSIM_new(GPS_SimulatorObj, ...
                    GPS_week,GPS_time,a2_E_prop_prev,chaserstates,tpropStep,thetaGMT,MJD_UTC,dt_GPS, ...
                    ConstantParameters,eopdata, Cnm, Snm, PC, flag_sc, centralbody, AuxilaryParameters, ChaserAppliedAccel./forceScale);
            end
        end
    else
        % Original ode45 propagation path retained for validation/regression checks.
        flag_sc = 1;
        [~,targetstates]=ode45(@(tau,states) dynamics.simulator(tau,states, Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody,  eopdata, ...
            PC, flag_sc, [0;0;0]),tpropGPS,[r1_I_prop; v1_I_prop],options);

        [~,targetattitude]=ode45(@(tau,states) dynamics.Attitude.simulator(tau,states,[0;0;0], ...
            [0;0;0], [0;0;0], inertiaMatrix_Target, inertiaMatrix_Target_inv),tpropGPS, ...
            [Target_Attitude_prop; Target_AngularVelocity_prop],options);

        r1_I_prop = targetstates(end,1:3)';
        v1_I_prop = targetstates(end,4:6)';
        Target_Attitude_prop = Rotations.NormalizeQuaternion(targetattitude(end,1:4)');
        Target_AngularVelocity_prop = targetattitude(end,5:7)';

        [~,chaserattitude]=ode45(@(tau,states) dynamics.Attitude.simulator(tau,states,ChaserAppliedTorque./max(1,(tpropGPS_length-1)), ...
            [0;0;0], [0;0;0], inertiaMatrix_Chaser, inertiaMatrix_Chaser_inv),tpropGPS, ...
            [Chaser_Attitude_prop; Chaser_AngularVelocity_prop],options);
        Chaser_Attitude_prop = Rotations.NormalizeQuaternion(chaserattitude(end,1:4)');
        Chaser_AngularVelocity_prop = chaserattitude(end,5:7)';

        nDataSteps = max(1,round(dt/dt_data));
        for j = 1:nDataSteps
            flag_sc = 2;
            [~,chaserstates]=ode45(@(tau,states) dynamics.simulator(tau,states, Cnm, Snm, ...
                ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody,  eopdata, ...
                PC, flag_sc, ChaserAppliedAccel./max(1,(tpropGPS_length-1))),tpropGPS,[r2_I_prop; v2_I_prop],options);
            chaserstates = chaserstates';
            r2_I_prop = chaserstates(1:3,end);
            v2_I_prop = chaserstates(4:6,end);

            if dt_GPS/dt_data == 1
                chaserstates = [chaserstates(:,1),chaserstates(:,end)];
            end

            if hardware_flags(2)
                [~,a2_E_prop_prev,GPS_week,GPS_time,thetaGMT,MJD_UTC,JD,GPS_Simulator_Clock] = GPS_Simulator.SetSpacecraftPosition_GPSSIM_new(GPS_SimulatorObj, ...
                    GPS_week,GPS_time,a2_E_prop_prev,chaserstates,tpropGPS,thetaGMT,MJD_UTC,dt_GPS, ...
                    ConstantParameters,eopdata, Cnm, Snm, PC, flag_sc, centralbody, AuxilaryParameters, ChaserAppliedAccel./max(1,(tpropGPS_length-1)));
            end
        end
    end
    SimulationTiming.propagation_sec = SimulationTiming.propagation_sec + toc(propagation_tic);

    posix_time_prop = posix_time_prop + dt;
    posix_time_sec = uint32(floor(posix_time_prop));
    posix_time_nsec = uint32((posix_time_prop-floor(posix_time_prop))*1e9);
    ROS_time = [posix_time_sec;posix_time_nsec];
    if rosEnabled && (SimulationOptions.publish_clock_every_step || rosPublishThisStep)
        ROS_fcns.publish_time2ros(Clock_ROS,msg_time,ROS_time);
    end
    tpre = t(i-1);

    elapsedBeforeWait = toc(ts);

    % Optional single-line simulation clock. Keep this before pause() so the
    % displayed status reflects the completed step and current wall-clock lag.
    if ClockDisplayState.enabled && ...
            (t(i-1) - ClockDisplayState.last_update_sim_time >= SimulationOptions.clock_display_period || i == length(t)+1)
        simTimeSec = t(i-1);
        hh = floor(simTimeSec/3600);
        mm = floor(mod(simTimeSec,3600)/60);
        ss = floor(mod(simTimeSec,60));
        if SimulationOptions.clock_display_wall_ratio && elapsedBeforeWait > 0
            realtimeFactor = simTimeSec / elapsedBeforeWait;
            lagSec = elapsedBeforeWait - targetWallTime;
            lineText = sprintf('Sim Time %02d:%02d:%02d | Wall %.2f s | RT %.3fx | Lag %+0.3f s', ...
                hh,mm,ss,elapsedBeforeWait,realtimeFactor,lagSec);
        else
            lineText = sprintf('Sim Time %02d:%02d:%02d',hh,mm,ss);
        end
        padCount = max(0,ClockDisplayState.last_line_length - length(lineText));
        fprintf('\r%s%s',lineText,repmat(' ',1,padCount));
        ClockDisplayState.last_line_length = length(lineText);
        ClockDisplayState.last_update_sim_time = simTimeSec;
    end

    if SimulationOptions.realtime_mode
        remainingTime = targetWallTime - elapsedBeforeWait;
        if remainingTime > 0
            % pause() yields the CPU. This prevents the old 100%% busy-wait behavior.
            pause(remainingTime);
            SimulationTiming.slack_sec(i-1) = remainingTime;
        else
            overrun = -remainingTime;
            SimulationTiming.overrun_sec(i-1) = overrun;
            SimulationTiming.overrun_count = SimulationTiming.overrun_count + 1;
            SimulationTiming.max_overrun_sec = max(SimulationTiming.max_overrun_sec,overrun);
            if SimulationOptions.verbose_timing && ...
                    SimulationTiming.overrun_count <= SimulationOptions.realtime_max_overrun_warnings
                fprintf('Real-time overrun at step %d: %.4f s behind wall clock.\n',i-1,overrun);
            end
        end
    end
    SimulationTiming.step_sec(i-1) = toc(step_tic);
end
if rosEnabled
    ROS_fcns.publish_data2ros(GNC_Run_ROS,msg_bool,false);
end
if exist('ClockDisplayState','var') && isfield(ClockDisplayState,'enabled') && ClockDisplayState.enabled
    fprintf('\n');
end
disp('Simulation completed successfully')
if exist('SimulationOptions','var') && isfield(SimulationOptions,'verbose_timing') && SimulationOptions.verbose_timing
    totalWallTime = toc(ts);
    simulatedTime = t(end);
    if totalWallTime > 0
        validStepCount = min(length(t),numel(SimulationTiming.step_sec));
        fprintf('Propagation time: %.3f s\n',SimulationTiming.propagation_sec);
        fprintf('Total wall time: %.3f s for %.3f s simulated time (%.3fx real time)\n', ...
            totalWallTime, simulatedTime, simulatedTime/totalWallTime);
        fprintf('Mean step wall time: %.6f s\n',mean(SimulationTiming.step_sec(1:validStepCount)));
    end
end
