function msg = std_msgs_Float64Struct
% Message struct definition for std_msgs/Float64
coder.inline("never")
msg = struct(...
    'MessageType','std_msgs/Float64',...
    'Data',ros.internal.ros.messages.ros.default_type('double',1));
coder.cstructname(msg,'std_msgs_Float64Struct_T');
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
