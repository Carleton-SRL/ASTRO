function [] = publish_time2ros(pub,msg,data)
%{
© 2025 Yazan Chihabi
%}
msg.Data.Sec = data(1);
msg.Data.Nsec = data(2);
send(pub,msg);
end