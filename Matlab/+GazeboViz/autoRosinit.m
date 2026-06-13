function masterURI = autoRosinit(masterURI)
%AUTOROSINIT Initialize MATLAB ROS1 connection for the Gazebo visualizer.
%
% masterURI may be:
%   'auto' or ''        -> detect WSL IP and use http://<ip>:11311
%   'localhost'         -> use http://localhost:11311
%   'http://IP:11311'   -> use the given ROS master URI
%
% This is intended for Windows MATLAB + WSL Ubuntu/ROS Noetic/Gazebo.

if nargin < 1 || isempty(masterURI)
    masterURI = 'auto';
end

% Return immediately if ROS is already active.
if GazeboViz.isRosActive()
    try
        fprintf('ROS is already initialized. Reusing existing MATLAB ROS node.\n');
    catch
    end
    return;
end

if strcmpi(masterURI,'auto')
    masterURI = GazeboViz.detectRosMasterURI();
elseif strcmpi(masterURI,'localhost')
    masterURI = 'http://localhost:11311';
end

fprintf('Initializing MATLAB ROS connection to %s ...\n', masterURI);
try
    rosinit(masterURI);
catch ME
    fprintf('\nFailed to initialize ROS using: %s\n', masterURI);
    fprintf('Make sure Gazebo/roslaunch is already running in WSL.\n');
    fprintf('In WSL, check the IP with: hostname -I\n');
    fprintf('Then in MATLAB you can set:\n');
    fprintf('  SimulationOptions.gazebo_master_uri = ''http://<WSL_IP>:11311'';\n\n');
    rethrow(ME);
end
end
