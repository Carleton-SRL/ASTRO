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
if hardware_flags(2)
    [GPS_Pos,GPS_Vel,Status_Receiver,GPS_week_Receiver,GPS_Time_Receiver,GPS_Time_Status] = GPS_Receiver.parserBESTXYZ(gpsObj.UserData);
end

k = 1;
tpre = 0;
ChaserAppliedAccel = [0;0;0];
ChaserAppliedTorque = [0;0;0];
ChaserGPS = [r2_I_prop;v2_I_prop;a2_I_prop];
ChaserGPS_prev = ChaserGPS;
if hardware_flags(1)
    ROS_fcns.publish_data2ros(GNC_Run_ROS,msg_bool,true);
end

for i = 2:length(t)+1
    if hardware_flags(1)
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
        
        if hardware_flags(1)
            ROS_fcns.publish_vector2ros(Chaser_GPS_Position_ROS,msg,ChaserGPS(1:3),ROS_time);
            ROS_fcns.publish_vector2ros(Chaser_GPS_Velocity_ROS,msg,ChaserGPS(4:6),ROS_time);
            ROS_fcns.publish_vector2ros(Chaser_GPS_Acceleration_ROS,msg,ChaserGPS(7:9),ROS_time);
            ROS_fcns.publish_data2ros(Chaser_GPS_Time_ROS,msg_UInt32MultiArray, ...
                uint32(GPS_TimeStamps_Receiver(:,i-1)));
            ROS_fcns.publish_data2ros(Chaser_GPS_Status_ROS,msg_bool,Status_Receiver);
        end
    end
    if hardware_flags(1)
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

    %% Vision Sensor Modelling
    if Sensor_flags(1)
        [range_chaser2target,angle_chaser2target] = SensorModels.LOS.Model([r1_I_prop; v1_I_prop], ...
            [r2_I_prop; v2_I_prop],LOS_std);
        if hardware_flags(1)
            ROS_fcns.publish_vector2ros(Chaser_Vision_ROS,msg, ...
                [range_chaser2target;angle_chaser2target] ,ROS_time);
        end
    end
    %% RADAR Sensor Modelling
    if Sensor_flags(2)
        [range_chaser2target_RADAR,angle_chaser2target_RADAR] = SensorModels.RADAR.Model([r1_I_prop; v1_I_prop], ...
            [r2_I_prop; v2_I_prop],RADAR_params,ConstantParameters);
        if hardware_flags(1)
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
            if hardware_flags(1)
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
            if hardware_flags(1)
                ROS_fcns.publish_data2ros(Chaser_TLE_flag_ROS,msg_bool,TLE_update);
                ROS_fcns.publish_data2ros(Chaser_Target_TLE_flag_ROS,msg_bool,TLE_update);
            end
        end
    end
    
    %% Sun & Moon Models
    if hardware_flags(1)
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
    if hardware_flags(1)
        ROS_fcns.publish_data2ros(Simulation_Clock_ROS,msg_float,t(i-1));
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

    flag_sc = 1;
    [~,targetstates]=ode45(@(t,states) dynamics.simulator(t,states, Cnm, Snm, ...
        ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody,  eopdata, ...
        PC, flag_sc, [0;0;0]),tpropGPS,[r1_I_prop; v1_I_prop],options);

    [~,targetattitude]=ode45(@(t,states) dynamics.Attitude.simulator(t,states,[0;0;0], ...
        [0;0;0], [0;0;0], inertiaMatrix_Target, inertiaMatrix_Target_inv),tpropGPS, ...
        [Target_Attitude_prop; Target_AngularVelocity_prop],options);

    r1_I_prop = targetstates(end,1:3)';
    v1_I_prop = targetstates(end,4:6)';

    Target_Attitude_prop = targetattitude(end,1:4)';
    Target_AngularVelocity_prop = targetattitude(end,5:7)';

    % Propagate Chaser Spacecraft
    [~,chaserattitude]=ode45(@(t,states) dynamics.Attitude.simulator(t,states,ChaserAppliedTorque./(tpropGPS_length-1), ...
        [0;0;0], [0;0;0], inertiaMatrix_Chaser, inertiaMatrix_Chaser_inv),tpropGPS, ...
        [Chaser_Attitude_prop; Chaser_AngularVelocity_prop],options);
    Chaser_Attitude_prop = chaserattitude(end,1:4)';
    Chaser_AngularVelocity_prop = chaserattitude(end,5:7)';
    % chaserattitude = dynamics.Attitude.propagator(dt_GPS, tpropGPS, [Chaser_Attitude_prop; Chaser_AngularVelocity_prop], ...
    %     ChaserAppliedTorque, [0;0;0], [0;0;0], inertiaMatrix_Chaser, inertiaMatrix_Chaser_inv);
    % Chaser_Attitude_prop = chaserattitude(1:4,end);
    % Chaser_AngularVelocity_prop = chaserattitude(5:7,end);

    for j = 1:dt/dt_data
        flag_sc = 2;
        [~,chaserstates]=ode45(@(t,states) dynamics.simulator(t,states, Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody,  eopdata, ...
            PC, flag_sc, ChaserAppliedAccel./(tpropGPS_length-1)),tpropGPS,[r2_I_prop; v2_I_prop],options); 
        chaserstates = chaserstates';
        r2_I_prop = chaserstates(1:3,end);
        v2_I_prop = chaserstates(4:6,end);
        

        if dt_GPS/dt_data == 1
            chaserstates = [chaserstates(:,1),chaserstates(:,end)];
        end

        % Set and send the chaser spacecraft's position in the GPS simulator
        if hardware_flags(2)
            [~,a2_E_prop_prev,GPS_week,GPS_time,thetaGMT,MJD_UTC,JD,GPS_Simulator_Clock] = GPS_Simulator.SetSpacecraftPosition_GPSSIM_new(GPS_SimulatorObj, ...
                GPS_week,GPS_time,a2_E_prop_prev,chaserstates,tpropGPS,thetaGMT,MJD_UTC,dt_GPS, ...
                ConstantParameters,eopdata, Cnm, Snm, PC, flag_sc, centralbody, AuxilaryParameters, ChaserAppliedAccel./(tpropGPS_length-1));
        end
    end
    
    posix_time_prop = posix_time_prop + dt;
    posix_time_sec = uint32(floor(posix_time_prop));
    posix_time_nsec = uint32((posix_time_prop-floor(posix_time_prop))*1e9);
    ROS_time = [posix_time_sec;posix_time_nsec];
    if hardware_flags(1)
        ROS_fcns.publish_time2ros(Clock_ROS,msg_time,ROS_time);
    end
    tpre = t(i-1);
    pause(0.001)
    while toc(ts)<t(i-1)
    end
end
if hardware_flags(1)
    ROS_fcns.publish_data2ros(GNC_Run_ROS,msg_bool,false);
end
disp('Simulation completed successfully')