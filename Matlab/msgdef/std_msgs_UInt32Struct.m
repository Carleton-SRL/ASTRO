function msg = std_msgs_UInt32Struct
% Message struct definition for std_msgs/UInt32
coder.inline("never")
msg = struct(...
    'MessageType','std_msgs/UInt32',...
    'Data',ros.internal.ros.messages.ros.default_type('uint32',1));
coder.cstructname(msg,'std_msgs_UInt32Struct_T');
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
