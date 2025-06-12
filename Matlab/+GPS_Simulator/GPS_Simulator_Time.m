function GPS_Simulator_Clock = GPS_Simulator_Time(t)
%{
© 2025 Yazan Chihabi
%}
Status = read(t);
GPS_Simulator_Clock = double(typecast(uint8(Status(end-4:end-1)),'uint32'));
end