function publish_gazebo_ephemeris_bodies(pubs, simTimeSec, MJD_UTC0, centralbody, ConstantParameters, eopdata, PC)
%PUBLISH_GAZEBO_EPHEMERIS_BODIES Publish Sun and Moon from ASTRO/JPL ephemeris.
if nargin < 1 || isempty(pubs), pubs = run_gazebo_visualizer(); end
if nargin < 2 || isempty(simTimeSec), simTimeSec = 0; end
[~,~,~,~,~,~,~,~,~,~,~,~,~,~,~,r_Moon,r_Sun,~,~,~,~,~,~,~,~] = ...
    time_variables.Julian_time(simTimeSec, MJD_UTC0, centralbody, ConstantParameters, eopdata, PC);
q = [0;0;0;1]; w = [0;0;0];
sunState = [r_Sun(:); [0;0;0]; q; w];
moonState = [r_Moon(:); [0;0;0]; q; w];
GazeboViz.publishInertialState(pubs.sun, sunState, pubs.frame_id, 'sun', pubs.quaternion_order);
GazeboViz.publishInertialState(pubs.moon, moonState, pubs.frame_id, 'moon', pubs.quaternion_order);
end
