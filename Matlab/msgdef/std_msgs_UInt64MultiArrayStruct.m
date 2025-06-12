function msg = std_msgs_UInt64MultiArrayStruct
% Message struct definition for std_msgs/UInt64MultiArray
coder.inline("never")
msg = struct(...
    'MessageType','std_msgs/UInt64MultiArray',...
    'Layout',std_msgs_MultiArrayLayoutStruct,...
    'Data',ros.internal.ros.messages.ros.default_type('uint64',NaN));
coder.cstructname(msg,'std_msgs_UInt64MultiArrayStruct_T');
coder.varsize('msg.Data',[1000000000 1],[1 0]);
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
