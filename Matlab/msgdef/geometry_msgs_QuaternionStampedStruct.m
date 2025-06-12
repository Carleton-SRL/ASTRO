function msg = geometry_msgs_QuaternionStampedStruct
% Message struct definition for geometry_msgs/QuaternionStamped
coder.inline("never")
msg = struct(...
    'MessageType','geometry_msgs/QuaternionStamped',...
    'Header',std_msgs_HeaderStruct,...
    'Quaternion',geometry_msgs_QuaternionStruct);
coder.cstructname(msg,'geometry_msgs_QuaternionStampedStruct_T');
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
