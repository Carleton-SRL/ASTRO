%% Space Flight Mechanics
%% Hardware-In-The-Loop Test-Bed Initialization Code
%{
This code defines the necessary functions and variables to run a
closed-loop simulation with the GPS simulator using one GPS receiver, Jetson 
computer hardware for deploying GNC via ROS, software models for vision and
RADAR sensors, and intermittent TLE updates.

A few notes to keep in mind with regards to the GPS:
1. The GPS simulator is currently only configured to run with one GPS
receiver in closed-loop. The second RF output is not currently functional
2. This test-bed performs in real-time, meaning the desired simulation
is exactly how long it will take in real-time to complete
3. The current GPS receiver being used, NOVATEL Flexpak6, only supports
near-circular or slightly elliptical orbits
4. Expect frequent GPS signal loss in this test-bed. This is due to the
fact that the GPS simulator accurately models Earth's ionosphere effects on
GPS satellite signals. South Atlantic anomaly affects LEO which is also 
modelled. On average, 45% of the time less than 4 satellites tracked [1].
At high latitudes (noon) sometimes no satellites tracked. Most signal 
losses occur between +/-5 and +/-20 degrees. 
5. Antenna default model 0db gain and 180 deg FOV, changed gain to 10db on 
L1,L2,L5 and FOV to 360 (omnidirectional). This can be changed within the
GPS simulator.

References:
[1] https://agupubs.onlinelibrary.wiley.com/doi/full/10.1002/2016SW001439
[2] https://phys.org/news/2016-10-swarm-reveals-gps-satellites-track.amp

© 2025 Yazan Chihabi

%}

%%
clear
clc
close all
format long
warning('off','all')
warning
cluster = parcluster;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Constants
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Physical constants
run('Physics_data/dataFCNini')
% centralbody(1) = Luni-solar third-body perturbations 1 for on, 0 for off
% centralbody(2) = gravity field perturbation 1 for on, 0 for off
% centralbody(3) = planetary third body perturbation 1 for on, 0 for off
% centralbody(4) = atmospheric drag perturbation 1 for on, 0 for off
% centralbody(5) = SRP perturbation 1 for on, 0 for off
% centralbody(6) = relativistic perturbation 1 for on, 0 for off
% centralbody(7) = solid Earth tides perturbation 1 for on, 0 for off
% centralbody(8) = ocean tides perturbation 1 for on, 0 for off
% centralbody(9) = gravity field degree (n)
% centralbody(10) = gravity field degree (m)
%
% Fidelity presets:
%   'fast'   : two-body only; fastest for debugging/controller iteration
%   'medium' : luni-solar + drag + SRP + 4x4 gravity field
%   'high'   : original high-fidelity model
%
% Execution presets:
%   'fast_offline' : maximum throughput. No real-time pacing, ROS, terminal clock,
%                    post-processing, or GPS-compatible 0.02 s propagation grid.
%   'realtime_hil' : wall-clock pacing with ROS/HIL-friendly propagation and clock.
%   'custom'       : edit individual SimulationOptions below.
SimulationOptions.execution_mode = 'gazebo_visualization';

switch lower(SimulationOptions.execution_mode)
    case 'gazebo_visualization'
        % Standalone Gazebo visualizer mode.
        % Launch Gazebo in WSL first, then run this script in MATLAB.
        % MATLAB auto-connects to the WSL ROS master and publishes inertial
        % [pos; vel; quat; omega] states as nav_msgs/Odometry.
        SimulationOptions.fidelity_mode = 'fast';
        SimulationOptions.use_fixed_step_propagator = true;
        SimulationOptions.gps_compatible_propagation = false;
        SimulationOptions.max_propagation_step = inf;
        SimulationOptions.realtime_mode = true;
        SimulationOptions.realtime_time_scale = 1.0;
        SimulationOptions.publish_ros = false;              % Heavy OBC ROS interface off
        SimulationOptions.publish_clock_every_step = false;
        SimulationOptions.show_simulation_clock = true;
        SimulationOptions.clock_display_period = 1.0;
        SimulationOptions.clock_display_wall_ratio = true;
        SimulationOptions.enable_postprocessing = false;
        SimulationOptions.verbose_timing = true;
        SimulationOptions.ros_publish_skip = inf;
        SimulationOptions.low_rate_ros_publish_skip = inf;
        SimulationOptions.enable_gazebo_visualizer = true;  % Lightweight Gazebo odometry topics on
        SimulationOptions.gazebo_auto_rosinit = true;
        SimulationOptions.gazebo_master_uri = 'auto';       % Uses `wsl hostname -I` on Windows
        SimulationOptions.gazebo_publish_skip = 1;
        SimulationOptions.gazebo_publish_celestials = true;
        SimulationOptions.gazebo_frame_id = 'eci';
        SimulationOptions.gazebo_quaternion_order = 'xyzw'; % ASTRO uses [qx qy qz qw]

    case 'fast_offline'
        SimulationOptions.fidelity_mode = 'fast';
        SimulationOptions.use_fixed_step_propagator = true;
        SimulationOptions.gps_compatible_propagation = false; % CRITICAL: avoids 0.02 s RK4 grid when GPS sim is off
        SimulationOptions.max_propagation_step = inf;         % one RK4 step over dt_data; avoids undefined dt before initialize_time
        SimulationOptions.realtime_mode = false;
        SimulationOptions.publish_ros = false;
        SimulationOptions.publish_clock_every_step = false;
        SimulationOptions.show_simulation_clock = false;
        SimulationOptions.clock_display_wall_ratio = false;
        SimulationOptions.enable_postprocessing = false;
        SimulationOptions.verbose_timing = true;
        SimulationOptions.ros_publish_skip = inf;
        SimulationOptions.low_rate_ros_publish_skip = inf;
        SimulationOptions.enable_gazebo_visualizer = false;
        SimulationOptions.gazebo_auto_rosinit = true;
        SimulationOptions.gazebo_master_uri = 'auto';
        SimulationOptions.gazebo_publish_skip = inf;
        SimulationOptions.gazebo_frame_id = 'eci';
        SimulationOptions.gazebo_quaternion_order = 'xyzw';

    case 'realtime_hil'
        SimulationOptions.fidelity_mode = 'medium';
        SimulationOptions.use_fixed_step_propagator = true;
        SimulationOptions.gps_compatible_propagation = true;
        SimulationOptions.max_propagation_step = 0.02;        % GPS-compatible substep; update if dt_GPS changes
        SimulationOptions.realtime_mode = true;
        SimulationOptions.realtime_time_scale = 1.0;
        SimulationOptions.publish_ros = true;
        SimulationOptions.publish_clock_every_step = true;
        SimulationOptions.show_simulation_clock = true;
        SimulationOptions.clock_display_period = 1.0;
        SimulationOptions.clock_display_wall_ratio = true;
        SimulationOptions.enable_postprocessing = false;
        SimulationOptions.verbose_timing = true;
        SimulationOptions.ros_publish_skip = 2;
        SimulationOptions.low_rate_ros_publish_skip = 5;
        SimulationOptions.enable_gazebo_visualizer = false;
        SimulationOptions.gazebo_auto_rosinit = true;
        SimulationOptions.gazebo_master_uri = 'auto';
        SimulationOptions.gazebo_publish_skip = 2;
        SimulationOptions.gazebo_frame_id = 'eci';
        SimulationOptions.gazebo_quaternion_order = 'xyzw';

    otherwise
        % Custom mode. Edit the values below as needed.
        SimulationOptions.fidelity_mode = 'fast';
        SimulationOptions.use_fixed_step_propagator = true;
        SimulationOptions.gps_compatible_propagation = false;
        SimulationOptions.max_propagation_step = inf;
        SimulationOptions.realtime_mode = false;
        SimulationOptions.publish_ros = false;
        SimulationOptions.publish_clock_every_step = false;
        SimulationOptions.show_simulation_clock = false;
        SimulationOptions.clock_display_period = 1.0;
        SimulationOptions.clock_display_wall_ratio = false;
        SimulationOptions.enable_postprocessing = false;
        SimulationOptions.verbose_timing = true;
        SimulationOptions.ros_publish_skip = inf;
        SimulationOptions.low_rate_ros_publish_skip = inf;
        SimulationOptions.enable_gazebo_visualizer = false;
        SimulationOptions.gazebo_auto_rosinit = true;
        SimulationOptions.gazebo_master_uri = 'auto';
        SimulationOptions.gazebo_publish_skip = inf;
        SimulationOptions.gazebo_frame_id = 'eci';
        SimulationOptions.gazebo_quaternion_order = 'xyzw';
end

SimulationOptions.realtime_time_scale = 1.0;          % 1.0 = wall-clock real time when realtime_mode=true
SimulationOptions.realtime_max_overrun_warnings = 20; % avoid flooding terminal

switch lower(SimulationOptions.fidelity_mode)
    case 'fast'
        centralbody = [0;0;0;0;0;0;0;0;0;0];
    case 'medium'
        centralbody = [1;1;0;1;1;0;0;0;4;4];
    otherwise
        centralbody = [1;1;1;1;1;1;1;1;8;8];
end

% hardware_flags(1) = OBC
% hardware_flags(2) = GPS Simulator
% hardware_flags(3) = GPS Receiver
hardware_flags = [false;false;false]; 

% GNC_flags(1) = Relative Navigation System
% GNC_flags(2) = Control System
% GNC_flags(3) = Guidance System
GNC_flags = [true;true;true];

% Sensor_flags(1) = Vision (Angle-only)
% Sensor_flags(2) = RADAR
% Sensor_flags(3) = TLEs
% Sensor_flags(4) = GPS
Sensor_flags = [false;true;true;true];

%% Spacecraft Initial Conditions (Inertial)
initialize_Spacecraft

%% Simulation Time
initialize_time

%% Initialize Spacecraft Inertial Accelerations
% X_ini = dynamics.TwoBody(0,[r2_I_ini;v2_I_ini],mu);
X_ini = dynamics.simulator(0,[r2_I_ini;v2_I_ini], Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_initial, centralbody,  eopdata, ...
            PC, 2, [0;0;0]);
a2_I_ini = X_ini(4:6);
jerk2_I_ini = [0;0;0];

%% Spacecraft Initial conditions in ECEF
initialize_Spacecraft_ECEF

%% Propagator Conditions
Propagator_Conditions

%% Initialize Sensors
SensorModels.initialize

%% Initialize Navigation
Navigation.initialize

%% Initialize Control
Control.initialize

%% Initialize ROS
if hardware_flags(1)
    initializeOBC_ROS
end

%% Initialize standalone Gazebo visualizer ROS publishers
% This is independent of the heavy OBC ROS interface above. It only publishes:
%   /astro/target/state
%   /astro/chaser/state
% as nav_msgs/Odometry using inertial [pos; vel; quat; omega].
GazeboVizPublishers = [];
if isfield(SimulationOptions,'enable_gazebo_visualizer') && SimulationOptions.enable_gazebo_visualizer
    try
        GazeboVizPublishers = run_gazebo_visualizer( ...
            'AutoInit', SimulationOptions.gazebo_auto_rosinit, ...
            'MasterURI', SimulationOptions.gazebo_master_uri, ...
            'FrameId', SimulationOptions.gazebo_frame_id, ...
            'QuaternionOrder', SimulationOptions.gazebo_quaternion_order);
    catch ME
        warning('Gazebo visualizer initialization failed: %s', ME.message);
        GazeboVizPublishers = [];
    end
end

%% GPS receiver initialization
if hardware_flags(3)
    GPS_Receiver.initialize_GPSReceiver
else
    pause(15)
end

%% Initialize GPS Simulator
if hardware_flags(2)
    GPS_Simulator.initialize_GPS_Simulator
end

%% Simulation
RunSimulation

%% Stop GPS Simulator
if hardware_flags(2)
    [Status] = GPS_Simulator.StopGPSSimulator(GPS_SimulatorObj);
end
%% Data Post-Processing
if ~exist('SimulationOptions','var') || ~isfield(SimulationOptions,'enable_postprocessing') || SimulationOptions.enable_postprocessing
    Results_PostProcessing.run
end

%%
if hardware_flags(1)
    rosshutdown
    stopCore(d)
end