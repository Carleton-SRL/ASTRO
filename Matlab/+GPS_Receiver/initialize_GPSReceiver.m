%{
© 2025 Yazan Chihabi
%}
% Creates a GPS receiver serial connection
disp('Initializng GPS Receiver...')
port = 'com3';
baudrate = 921600;
gpsObj = serialport(port,baudrate);
configureTerminator(gpsObj,'CR/LF');
configureCallback(gpsObj,"terminator",@GPS_Receiver.ReadGPS_Receiver)

writeline(gpsObj,"reset")
pause(10)
writeline(gpsObj,['SETAPPROXTIME',' ',sprintf('%.0f',GPS_week),' ',sprintf('%.0f',GPS_time)])
pause(5)
writeline(gpsObj,['SETAPPROXPOS',' ',sprintf('%.0f',lla_ini(1)),' ',sprintf('%.0f',lla_ini(2)) ...
    ,' ',sprintf('%.0f',lla_ini(3))])
disp('GPS Receiver initialized')