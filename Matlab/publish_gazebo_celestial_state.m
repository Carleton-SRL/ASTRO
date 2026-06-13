function publish_gazebo_celestial_state(pubs, sunState, moonState)
%PUBLISH_GAZEBO_CELESTIAL_STATE Publish Sun and Moon inertial states to Gazebo.
% State format is [pos; vel; quat; omega], with scalar-last quaternion [qx;qy;qz;qw].

if nargin < 1 || isempty(pubs)
    pubs = run_gazebo_visualizer();
end
q = [0;0;0;1];
w = [0;0;0];
if nargin < 2 || isempty(sunState)
    sunState = [[1.496e8;0;0]; [0;0;0]; q; w]; % km demo Sun position
end
if nargin < 3 || isempty(moonState)
    moonState = [[384400;0;0]; [0;0;0]; q; w]; % km demo Moon position
end
GazeboViz.publishInertialState(pubs.sun, sunState, pubs.frame_id, 'sun', pubs.quaternion_order);
GazeboViz.publishInertialState(pubs.moon, moonState, pubs.frame_id, 'moon', pubs.quaternion_order);
end
