function [] = publish_data2ros(pub,msg,data)
%{
© 2025 Yazan Chihabi
%}
msg.Data = data;
send(pub,msg);
end