function ReadGPS_Simulator(t,evt)
%{
© 2025 Yazan Chihabi
%}
data = read(t);
t.UserData = double(typecast(uint8(data),'uint32'));
end