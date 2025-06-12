function msg = geometry_msgs_Vector3StampedStruct
% Message struct definition for geometry_msgs/Vector3Stamped
coder.inline("never")
msg = struct(...
    'MessageType','geometry_msgs/Vector3Stamped',...
    'Header',std_msgs_HeaderStruct,...
    'Vector',geometry_msgs_Vector3Struct);
coder.cstructname(msg,'geometry_msgs_Vector3StampedStruct_T');
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
