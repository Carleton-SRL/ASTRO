%{
© 2025 Yazan Chihabi
%}
%% Initialize the GPS simulator
disp('Initializing GPS Simulator...')
GPS_SimulatorObj = tcpclient("169.254.212.255",5307,"Timeout",1);
GPS_time= GPS_time*1000;
[Status] = GPS_Simulator.initialize_GPSSIM(GPS_SimulatorObj,GPS_time,GPS_week,r2_E_ini);
ts = tic;
timeOut = 0.1;
while toc(ts)<timeOut
    if ~isempty(Status)
        break
    else
        [Status] = GPS_SimulatorObj.initialize_GPSSIM(GPS_SimulatorObj,GPS_time,GPS_week,r2_E_ini);
    end
end
disp('GPS Simulator Initialized')