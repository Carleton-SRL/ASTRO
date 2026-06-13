function publishInertialState(pub, state, frameId, childFrameId, quatOrder)
%PUBLISHINERTIALSTATE Publish [pos; vel; quat; omega] as nav_msgs/Odometry.
% state = [x;y;z; vx;vy;vz; q; wx;wy;wz]
% q can be scalar-first [qw;qx;qy;qz] or scalar-last [qx;qy;qz;qw].
% Position units are not changed here. Set Gazebo launch arg position_units:=km or m.

if nargin < 4 || isempty(childFrameId), childFrameId = 'spacecraft'; end
if nargin < 5 || isempty(quatOrder), quatOrder = 'wxyz'; end
if numel(state) ~= 13
    error('State must be 13x1: [pos(3); vel(3); quat(4); omega(3)].');
end
state = state(:);
pos = state(1:3);
vel = state(4:6);
q = state(7:10);
omega = state(11:13);
q = q ./ max(norm(q), eps);

if strcmpi(quatOrder,'wxyz')
    qw = q(1); qx = q(2); qy = q(3); qz = q(4);
elseif strcmpi(quatOrder,'xyzw')
    qx = q(1); qy = q(2); qz = q(3); qw = q(4);
else
    error('quatOrder must be ''wxyz'' or ''xyzw''.');
end

msg = rosmessage(pub);
msg.Header.Stamp = rostime('now');
msg.Header.FrameId = frameId;
msg.ChildFrameId = childFrameId;
msg.Pose.Pose.Position.X = pos(1);
msg.Pose.Pose.Position.Y = pos(2);
msg.Pose.Pose.Position.Z = pos(3);
msg.Pose.Pose.Orientation.W = qw;
msg.Pose.Pose.Orientation.X = qx;
msg.Pose.Pose.Orientation.Y = qy;
msg.Pose.Pose.Orientation.Z = qz;
msg.Twist.Twist.Linear.X = vel(1);
msg.Twist.Twist.Linear.Y = vel(2);
msg.Twist.Twist.Linear.Z = vel(3);
msg.Twist.Twist.Angular.X = omega(1);
msg.Twist.Twist.Angular.Y = omega(2);
msg.Twist.Twist.Angular.Z = omega(3);
send(pub,msg);
end
