function [] = publish_quat2ros(pub,msg,data,time)
%{
© 2025 Yazan Chihabi
%}
msg.Header.Stamp.Sec = time(1);
msg.Header.Stamp.Nsec = time(2);
msg.Quaternion.X = data(1);
msg.Quaternion.Y = data(2);
msg.Quaternion.Z = data(3);
msg.Quaternion.W = data(4);
send(pub,msg);
end