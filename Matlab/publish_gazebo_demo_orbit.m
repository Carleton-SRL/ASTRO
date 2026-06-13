function publish_gazebo_demo_orbit(durationSec)
%PUBLISH_GAZEBO_DEMO_ORBIT Demo publisher for the Gazebo visualizer.
% Run after:
%   rosinit('http://<WSL_IP>:11311')
%   pubs = run_gazebo_visualizer();

if nargin < 1, durationSec = 120; end
pubs = run_gazebo_visualizer();
rate = robotics.Rate(20);
R = 7000;          % km, target inertial orbit radius for demonstration
rho = 0.2;         % km, relative chaser offset amplitude
n = 0.001;         % rad/s demo angular rate
q = [0;0;0;1];   % scalar-last identity quaternion [qx;qy;qz;qw]
w = [0;0;0.01];

t0 = tic;
while toc(t0) < durationSec
    t = toc(t0);
    rt = [R*cos(n*t); R*sin(n*t); 0];
    vt = [-R*n*sin(n*t); R*n*cos(n*t); 0];
    rel = [rho*cos(0.1*t); rho*sin(0.1*t); 0.05*sin(0.05*t)];
    relv = [-rho*0.1*sin(0.1*t); rho*0.1*cos(0.1*t); 0.05*0.05*cos(0.05*t)];
    targetState = [rt; vt; q; w];
    chaserState = [rt+rel; vt+relv; q; w];

    % Demo Sun/Moon inertial positions in km. They are scaled separately by Gazebo.
    sunState  = [[1.496e8; 0; 0]; [0;0;0]; q; [0;0;0]];
    moonState = [[384400*cos(0.005*t); 384400*sin(0.005*t); 30000*sin(0.002*t)]; [0;0;0]; q; [0;0;0]];

    GazeboViz.publishInertialState(pubs.target,targetState,pubs.frame_id,pubs.child_target,pubs.quaternion_order);
    GazeboViz.publishInertialState(pubs.chaser,chaserState,pubs.frame_id,pubs.child_chaser,pubs.quaternion_order);
    GazeboViz.publishInertialState(pubs.sun,sunState,pubs.frame_id,'sun',pubs.quaternion_order);
    GazeboViz.publishInertialState(pubs.moon,moonState,pubs.frame_id,'moon',pubs.quaternion_order);
    waitfor(rate);
end
end
