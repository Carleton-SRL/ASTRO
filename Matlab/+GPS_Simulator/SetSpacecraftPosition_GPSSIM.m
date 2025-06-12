function [Status] = SetSpacecraftPosition_GPSSIM(t,GPS_time,r,v,a,jerk)
%{
© 2025 Yazan Chihabi
%}
%% Sends initialization command
% Time  = Simulation time in seconds
% r     = spacecraft position in ECEF (km)
% v     = spacecraft position in ECEF (km/s)
% a     = spacecraft acceleration in ECEF (km/s2)
% jerk = spacecraft jerk in ECEF (km/s3)

% Convert position, velocity, acceleration and jerk to meters 

r = r.*(10^3);

v = v.*(10^3);

a = a.*(10^3);

jerk = jerk.*(10^3);

% Quantize position, velocity, acceleration and jerk to fixed-point

% r_fi = fi(r, 1, 32, 1e-2, 0);
% v_fi = fi(v, 1, 32, 1e-5, 0);
% a_fi = fi(a, 1, 16, 1e-2, 0);
% jerk_fi = fi(jerk, 1, 16, 1e-2, 0);

[r_fi,v_fi,a_fi,jerk_fi] = QuantizeStates(r,v,a,jerk);

rx = typecast(r_fi(1),'uint8');
ry = typecast(r_fi(2),'uint8');
rz = typecast(r_fi(3),'uint8');

vx = typecast(v_fi(1),'uint8');
vy = typecast(v_fi(2),'uint8');
vz = typecast(v_fi(3),'uint8');

ax = typecast(a_fi(1),'uint8');
ay = typecast(a_fi(2),'uint8');
az = typecast(a_fi(3),'uint8');

jerkx = typecast(jerk_fi(1),'uint8');
jerky = typecast(jerk_fi(2),'uint8');
jerkz = typecast(jerk_fi(3),'uint8');

% Typecast time into uint8 for transfer

time = typecast(uint32(GPS_time),'uint8');

% % Quantize position
% 
% rx_fi = r_fi(1);
% ry_fi = r_fi(2);
% rz_fi = r_fi(3);
% 
% rx_binary = rx_fi.bin;
% rx_binary = reshape(rx_binary,[8,4]);
% rx_binary = flip(rx_binary');
% rx = uint8(bin2dec(rx_binary));
% 
% ry_binary = ry_fi.bin;
% ry_binary = reshape(ry_binary,[8,4]);
% ry_binary = flip(ry_binary');
% ry = uint8(bin2dec(ry_binary));
% 
% rz_binary = rz_fi.bin;
% rz_binary = reshape(rz_binary,[8,4]);
% rz_binary = flip(rz_binary');
% rz = uint8(bin2dec(rz_binary));
% 
% % Quantize velocity
% 
% vx_fi = v_fi(1);
% vy_fi = v_fi(2);
% vz_fi = v_fi(3);
% 
% vx_binary = vx_fi.bin;
% vx_binary = reshape(vx_binary,[8,4]);
% vx_binary = flip(vx_binary');
% vx = uint8(bin2dec(vx_binary));
% 
% vy_binary = vy_fi.bin;
% vy_binary = reshape(vy_binary,[8,4]);
% vy_binary = flip(vy_binary');
% vy = uint8(bin2dec(vy_binary));
% 
% vz_binary = vz_fi.bin;
% vz_binary = reshape(vz_binary,[8,4]);
% vz_binary = flip(vz_binary');
% vz = uint8(bin2dec(vz_binary));
% 
% % Quantize Acceleration
% 
% ax_fi = a_fi(1);
% ay_fi = a_fi(2);
% az_fi = a_fi(3);
% 
% ax_binary = ax_fi.bin;
% ax_binary = reshape(ax_binary,[8,2]);
% ax_binary = flip(ax_binary');
% ax = uint8(bin2dec(ax_binary));
% 
% ay_binary = ay_fi.bin;
% ay_binary = reshape(ay_binary,[8,2]);
% ay_binary = flip(ay_binary');
% ay = uint8(bin2dec(ay_binary));
% 
% az_binary = az_fi.bin;
% az_binary = reshape(az_binary,[8,2]);
% az_binary = flip(az_binary');
% az = uint8(bin2dec(az_binary));
% 
% % Quantize Jerk
% 
% jerkx_fi = jerk_fi(1);
% jerky_fi = jerk_fi(2);
% jerkz_fi = jerk_fi(3);
% 
% jerkx_binary = jerkx_fi.bin;
% jerkx_binary = reshape(jerkx_binary,[8,2]);
% jerkx_binary = flip(jerkx_binary');
% jerkx = uint8(bin2dec(jerkx_binary));
% 
% jerky_binary = jerky_fi.bin;
% jerky_binary = reshape(jerky_binary,[8,2]);
% jerky_binary = flip(jerky_binary');
% jerky = uint8(bin2dec(jerky_binary));
% 
% jerkz_binary = jerkz_fi.bin;
% jerkz_binary = reshape(jerkz_binary,[8,2]);
% jerkz_binary = flip(jerkz_binary');
% jerkz = uint8(bin2dec(jerkz_binary));

% Create data for transfer
% data = [uint8(11);uint8(19);time';rx;ry;rz];
% data = [uint8(11);uint8(31);time';rx;ry;rz;
%     vx;vy;vz];
% data = [uint8(11);uint8(37);time';rx;ry;rz;
%     vx;vy;vz;ax;ay;az];
% data = [uint8(11);uint8(43);time';rx;ry;rz;
%     vx;vy;vz;ax;ay;az;jerkx;jerky;jerkz]; 
data = [uint8(11);uint8(43);time';rx';ry';rz';
    vx';vy';vz';ax';ay';az';jerkx';jerky';jerkz']; 

checksum = Checksum(data);

data = [data;checksum];

% Transfer data
% ts = tic;
% timeOut = 0.5;
% while toc(ts)<timeOut
    write(t, data,"uint8");

% end

% % Read Status
Status = read(t);
% ts = tic;
% while toc(ts)<0.1
%     write(t, data,"uint8");
% end
% Status = read(t);
% ts = tic;
% timeOut = 0.5;
% while toc(ts)<timeOut
%     if ~isempty(Status)
% %         if length(Status) == 5 && Status(4) == 0
%            break
% %         else
% %             write(t, data,"uint8");
% %             while toc(ts)<0.1
% %             end
% %             Status = read(t);
% %         end
%     else
% %         write(t, data,"uint8");
% %         while toc(ts)<0.1
% %         end
%         Status = read(t);
%     end
% end



% ts = tic;
% timeOut = 0.5;
% while toc(ts)<timeOut
%     write(t, data,"uint8");
%     Status = read(t);
    if ~isempty(Status)
        GPS_Simulator_Clock = double(typecast(uint8(Status(end-4:end-1)),'uint32'));
        while GPS_time - GPS_Simulator_Clock > 0
%             write(t, data,"uint8");
            Status = read(t);
            while isempty(Status)
                Status = read(t);
            end
            GPS_Simulator_Clock = double(typecast(uint8(Status(end-4:end-1)),'uint32'));
        end
%         if GPS_time - GPS_Simulator_Clock > 0
%                 break
%         end
%     else
%         Status = read(t);
    end
% end
end