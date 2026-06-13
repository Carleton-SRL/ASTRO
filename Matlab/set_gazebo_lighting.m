function set_gazebo_lighting(modeOrDirection, intensity)
%SET_GAZEBO_LIGHTING Change Gazebo visualizer lighting in real time.
if nargin < 1 || isempty(modeOrDirection), modeOrDirection = 'day'; end
GazeboViz.autoRosinit('auto');
if isnumeric(modeOrDirection)
    v = modeOrDirection(:);
    if numel(v) ~= 3, error('Custom lighting direction must be a 3x1 vector.'); end
    pub = rospublisher('/astro/viz/sun_direction','geometry_msgs/Vector3');
    msg = rosmessage(pub); msg.X = v(1); msg.Y = v(2); msg.Z = v(3); send(pub,msg);
    fprintf('Gazebo sun direction published: [%.3g %.3g %.3g]
', v(1), v(2), v(3));
else
    pub = rospublisher('/astro/viz/lighting_mode','std_msgs/String');
    msg = rosmessage(pub); msg.Data = char(modeOrDirection); send(pub,msg);
    fprintf('Gazebo lighting mode published: %s
', msg.Data);
end
if nargin >= 2 && ~isempty(intensity)
    ipub = rospublisher('/astro/viz/light_intensity','std_msgs/Float64');
    imsg = rosmessage(ipub); imsg.Data = double(intensity); send(ipub, imsg);
    fprintf('Gazebo light intensity published: %.3g
', imsg.Data);
end
end
