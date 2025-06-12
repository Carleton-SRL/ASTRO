function msg = std_msgs_TimeStruct
% Message struct definition for std_msgs/Time
coder.inline("never")
msg = struct(...
    'MessageType','std_msgs/Time',...
    'Data',ros_TimeStruct);
coder.cstructname(msg,'std_msgs_TimeStruct_T');
if ~isempty(coder.target)
    coder.ceval('//',coder.rref(msg));
end
end
