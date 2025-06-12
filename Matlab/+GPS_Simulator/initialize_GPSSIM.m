%{
© 2025 Yazan Chihabi
%}
function [Status] = initialize_GPSSIM(t,time,GPS_week,r_ini)

%% Sends initialization command
% Time = Simulation start time in seconds
% GPS_week = Simulation start week
% r_ini = spacecraft starting position in ECEF (km)

% Position must be converted to meters (multiply by 1000) 
% then scaled by 10^-2 -> final scale by 10

x = r_ini(1)*1000;
y = r_ini(2)*1000;
z = r_ini(3)*1000;

% Typecast everything into uint8 for transfer
time = typecast(uint32(time),'uint8');
GPS_week = typecast(uint16(GPS_week),'uint8');

% Quantize position

x_fi = fi(x, 1, 32, 1e-02, 0);
y_fi = fi(y, 1, 32, 1e-02, 0);
z_fi = fi(z, 1, 32, 1e-02, 0);

x_binary = x_fi.bin;
x_binary = reshape(x_binary,[8,4]);
x_binary = flip(x_binary');
x = uint8(bin2dec(x_binary));

y_binary = y_fi.bin;
y_binary = reshape(y_binary,[8,4]);
y_binary = flip(y_binary');
y = uint8(bin2dec(y_binary));

z_binary = z_fi.bin;
z_binary = reshape(z_binary,[8,4]);
z_binary = flip(z_binary');
z = uint8(bin2dec(z_binary));

% x = typecast(single(x),'uint8');
% y = typecast(single(y),'uint8');
% z = typecast(single(z),'uint8');

% Create data for transfer
% data = [uint8(1);uint8(22);uint8(0);time';GPS_week';x;y;z]; %sec
data = [uint8(52);uint8(22);uint8(0);time';GPS_week';x;y;z]; %msec
checksum = GPS_Simulator.Checksum(data);
data = [data;checksum];

% Transfer data
write(t, data,"uint8");
% Read Status
Status = read(t);
ts = tic;
timeOut = 0.5;
while toc(ts)<timeOut
    if ~isempty(Status)
        break
    else
        Status = read(t);
    end
end

%% Set GPS simulator to output clock time
data = [uint8(16);uint8(3)];
checksum = GPS_Simulator.Checksum(data);
data = [data;checksum];
write(t, data,"uint8");
read(t);

end