%{
© 2025 Yazan Chihabi
%}
disp('Initializing sensor models...')
SensorModels.LOS.initialize % initialize LOS sensors
SensorModels.RADAR.initialize % initialize RADAR sensors
SensorModels.TLE.initialize % initialize TLE update
disp('Sensor models initialized.')