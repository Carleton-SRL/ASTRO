function [Status] = StopGPSSimulator(GPS_SimulatorObj)
%{
© 2025 Yazan Chihabi
%}
disp('Stopping GPS Simulator...')
data = [uint8(22);uint8(3)];
checksum = GPS_Simulator.Checksum(data);
data = [data;checksum];
write(GPS_SimulatorObj, data,"uint8");
pause(5);
Status = read(GPS_SimulatorObj);
disp('GPS Simulator Stopped')
end