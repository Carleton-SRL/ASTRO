function pubs = run_gazebo_visualizer(varargin)
%RUN_GAZEBO_VISUALIZER Initialize ROS if needed and create Gazebo publishers.
%
% This function is safe to call from initialization.m. It will auto-detect the
% WSL ROS master using `wsl hostname -I` when running MATLAB on Windows.
%
% Topics:
%   /astro/target/state  nav_msgs/Odometry
%   /astro/chaser/state  nav_msgs/Odometry
%
% State format expected by GazeboViz.publishInertialState:
%   [pos; vel; quat; omega]
% where pos = 3x1, vel = 3x1, quat = 4x1, omega = 3x1.
%
% ASTRO attitude convention is scalar-last [qx qy qz qw], so the default
% quaternion_order is 'xyzw'.
%
% Optional name/value pairs:
%   'AutoInit'        true/false
%   'MasterURI'       'auto', 'localhost', or 'http://<ip>:11311'
%   'FrameId'         default 'eci'
%   'QuaternionOrder' default 'xyzw'

opts.AutoInit = true;
opts.MasterURI = 'auto';
opts.FrameId = 'eci';
opts.QuaternionOrder = 'xyzw';

if mod(numel(varargin),2) ~= 0
    error('run_gazebo_visualizer expects name/value pairs.');
end
for k = 1:2:numel(varargin)
    name = varargin{k};
    value = varargin{k+1};
    if ~ischar(name) && ~isstring(name)
        error('Option names must be strings.');
    end
    name = char(name);
    if isfield(opts,name)
        opts.(name) = value;
    else
        % case-insensitive fallback
        fields = fieldnames(opts);
        idx = find(strcmpi(fields,name),1);
        if isempty(idx)
            error('Unknown option: %s', name);
        end
        opts.(fields{idx}) = value;
    end
end

if opts.AutoInit
    GazeboViz.autoRosinit(opts.MasterURI);
elseif ~GazeboViz.isRosActive()
    error('ROS is not initialized. Either run rosinit(...) first or call run_gazebo_visualizer(''AutoInit'',true).');
end

pubs.target = rospublisher('/astro/target/state','nav_msgs/Odometry');
pubs.chaser = rospublisher('/astro/chaser/state','nav_msgs/Odometry');
pubs.sun    = rospublisher('/astro/sun/state','nav_msgs/Odometry');
pubs.moon   = rospublisher('/astro/moon/state','nav_msgs/Odometry');
pubs.lighting_mode = rospublisher('/astro/viz/lighting_mode','std_msgs/String');
pubs.sun_direction = rospublisher('/astro/viz/sun_direction','geometry_msgs/Vector3');
pubs.light_intensity = rospublisher('/astro/viz/light_intensity','std_msgs/Float64');
pubs.frame_id = opts.FrameId;
pubs.child_target = 'target';
pubs.child_chaser = 'chaser';
pubs.quaternion_order = opts.QuaternionOrder;

fprintf('ASTRO Gazebo visualizer ROS publishers ready:\n');
fprintf('  ROS master: %s\n', char(opts.MasterURI));
fprintf('  /astro/target/state  nav_msgs/Odometry\n');
fprintf('  /astro/chaser/state  nav_msgs/Odometry\n');
fprintf('  /astro/sun/state     nav_msgs/Odometry\n');
fprintf('  /astro/moon/state    nav_msgs/Odometry\n');
fprintf('  /astro/viz/lighting_mode std_msgs/String\n');
fprintf('  /astro/viz/light_intensity std_msgs/Float64\n');
fprintf('  quaternion order: %s\n', pubs.quaternion_order);
end
