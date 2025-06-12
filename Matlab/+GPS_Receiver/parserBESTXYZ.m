function [Pos,Vel,Status,GPS_Week,GPS_Time,GPS_Time_Status] = parserBESTXYZ(unparsedData)
%{
© 2025 Yazan Chihabi
%}
% 0 SOL_COMPUTED Solution computed
% 1 INSUFFICIENT_OBS Insufficient observations
% 2 NO_CONVERGENCE No convergence
% 3 SINGULARITY Singularity at parameters matrix
% 4 COV_TRACE Covariance trace exceeds maximum (trace > 1000 m)
% 5 TEST_DIST Test distance exceeded (maximum of 3 rejections if distance >10 km)
% 6 COLD_START Not yet converged from cold start
% 7 V_H_LIMIT Height or velocity limits exceeded (in accordance with export licensing
% restrictions)
% 8 VARIANCE Variance exceeds limits
% 9 RESIDUALS Residuals are too large
% 13 INTEGRITY_WARNING Large residuals make position unreliable
% 18 PENDING
% When a FIX POSITION command is entered, the receiver computes its
% own position and determines if the fixed position is valid 
% PENDING implies there are not enough satellites currently tracked to verify
% if the FIX POSITION entered into thereceiver is valid. Under normal conditions,
% you should only see PENDING for a few seconds on power up before the GNSS
% receiver has locked onto its first few satellites. If your antenna is obstructed 
% (or not plugged in) and you have entered a FIX POSITION command, then you 
% may see PENDING indefinitely
% 19 INVALID_FIX The fixed position, entered using the FIX POSITION command, is not
% valid

% 20 UNKNOWN Time validity is unknown
% 60 APPROXIMATE Time is set approximately
% 80 COARSEADJUSTING Time is approaching coarse precision
% 100 COARSE This time is valid to coarse precision
% 120 COARSESTEERING Time is coarse set and is being steered
% 130 FREEWHEELING Position is lost and the range bias cannot be calculated
% 140 FINEADJUSTING Time is adjusting to fine precision
% 160 FINE Time has fine precision
% 170 FINEBACKUPSTEERING Time is fine set and is being steered by the backup system
% 180 FINESTEERING Time is fine set and is being steered
% 200 SATTIME Time from satellite. Only used in logs containing satellite
% data such as ephemeris and almanac

Pos = zeros(6,1);
Vel = zeros(6,1);
Status = false;
splitString = split(unparsedData,[",",";"]);

if contains(splitString(11),["SOL_COMPUTED","INTEGRITY_WARNING"]) %,"INTEGRITY_WARNING"
    Pos = [str2double(splitString{13});
        str2double(splitString{14});
        str2double(splitString{15});
        str2double(splitString{16});
        str2double(splitString{17});
        str2double(splitString{18})];

    Vel = [str2double(splitString{21});
        str2double(splitString{22});
        str2double(splitString{23});
        str2double(splitString{24});
        str2double(splitString{25});
        str2double(splitString{26})];

    Status = true;

    
end
GPS_Week = str2double(splitString{6});
GPS_Time = str2double(splitString{7});
GPS_Time_Status = splitString{5};

Pos = Pos./1000;
Vel = Vel./1000;
end