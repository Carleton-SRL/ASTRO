function [Status,a_E_prop_prev,GPS_Week,GPS_time,thetaGMT,MJD_UTC,JD,GPS_Simulator_Clock] = SetSpacecraftPosition_GPSSIM_new(t, ...
    GPS_Week,GPS_time,a_E_prop_prev,chaserstates,tprop,thetaGMT,MJD_UTC,dt, ...
    ConstantParameters,eopdata, Cnm, Snm, PC, flag_sc, centralbody, AuxilaryParameters, u)
%{
© 2025 Yazan Chihabi
%}
%% Sends initialization command
% Time  = Simulation time in seconds
% r     = spacecraft position in ECEF (km)
% v     = spacecraft position in ECEF (km/s)
% a     = spacecraft acceleration in ECEF (km/s2)
% jerk = spacecraft jerk in ECEF (km/s3)

l = length(tprop);

r_I = chaserstates(1:3,2:end);
v_I = chaserstates(4:6,2:end);

u = u./(l-1);

%Julian Date


data = zeros(43*(l-1),1);
for j = 1:l-1
    % Propagate time variables
    GPS_time = GPS_time + dt*1000;
    if GPS_time> 604799999
        GPS_time = 0;
        GPS_Week = GPS_Week + 1;
    end
    MJD_UTC = MJD_UTC+dt/86400;
    JD = MJD_UTC+2400000.5;
    
    % Calculate accelerations
    X_prop = dynamics.simulator(0,[r_I(:,j);v_I(:,j)], Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_UTC, centralbody,  eopdata, ...
            PC, flag_sc, u);
    a_I_prop = X_prop(4:6);
    
    % Convert to ECEF
    [r_E_prop,v_E_prop,a_E_prop,LOD] = Rotations.ECI2ECEF(MJD_UTC, [r_I(:,j); v_I(:,j);a_I_prop], ConstantParameters, eopdata);
    wE = ConstantParameters.omega_Earth-0.843994809*1e-9*LOD;
    thetaGMT = thetaGMT+wE*dt;
    
    jerk_E_prop = (a_E_prop - a_E_prop_prev)/dt;
    a_E_prop_prev = a_E_prop;

    r = r_E_prop;
    v = v_E_prop;
    a = a_E_prop;
    jerk = jerk_E_prop;

    % Convert position, velocity, acceleration and jerk to meters 

    r = r.*(10^3);
    
    v = v.*(10^3);
    
    a = a.*(10^3);
    
    jerk = jerk.*(10^3);

    % Quantize position, velocity, acceleration and jerk to fixed-point

    [r_fi,v_fi,a_fi,jerk_fi] = GPS_Simulator.QuantizeStates(r,v,a,jerk);
    
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
    
    % Create data for transfer
    data_temp = [uint8(11);uint8(43);time';rx';ry';rz';
        vx';vy';vz';ax';ay';az';jerkx';jerky';jerkz']; 
    
    checksum = GPS_Simulator.Checksum(data_temp);
    
    data(1+(j-1)*43:j*43) = [data_temp;checksum];
%     write(t, data(1+(j-1)*43:j*43),"uint8");
end




% Transfer data
if l-1<=100
    write(t, data,"uint8");
else
    l_write = (l-1)/100;
    for j = 1:l_write
        write(t, data(1+(j-1)*100*43:j*100*43),"uint8");
        % ts = tic;
        % while toc(ts)<0.08
        % end
    end
end

% Read data
Status = read(t);
while 1
    if ~isempty(Status)
        GPS_Simulator_Clock = double(typecast(uint8(Status(end-4:end-1)),'uint32'));
        while GPS_time - GPS_Simulator_Clock > 0
            Status = read(t);
            while isempty(Status)
                Status = read(t);
            end
            GPS_Simulator_Clock = double(typecast(uint8(Status(end-4:end-1)),'uint32'));
        end
        break
    end
    Status = read(t);
end


end