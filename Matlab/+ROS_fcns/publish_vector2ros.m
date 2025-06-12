function [] = publish_vector2ros(pub,msg,data,time)
%{
© 2025 Yazan Chihabi
%}
msg.Header.Stamp.Sec = time(1);
msg.Header.Stamp.Nsec = time(2);
msg.Vector.X = data(1);
msg.Vector.Y = data(2);
msg.Vector.Z = data(3);
send(pub,msg);
end