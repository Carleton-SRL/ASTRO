function ReadGPS_Receiver(gpsObj,evt)
%{
© 2025 Yazan Chihabi
%}
data = readline(gpsObj);
gpsObj.UserData = data;
end