function tf = isRosActive()
%ISROSACTIVE True when MATLAB already has an active ROS node.
tf = false;
try
    tf = robotics.ros.internal.Global.isNodeActive ~= 0;
catch
    try
        rostopic('list');
        tf = true;
    catch
        tf = false;
    end
end
end
