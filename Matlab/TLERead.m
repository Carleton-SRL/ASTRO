function [a,e,w,inc,RAAN,tano,M,E,B] = TLERead(fname,mu)
% Finds the classical orbital elements from a true-line element file
% Copyright Yazan Chihabi
% References:
%

fid = fopen(fname, 'rb');
% 19-32	04236.56031392	Element Set Epoch (UTC)
% 3-7	25544	Satellite Catalog Number
% 9-16	51.6335	Orbit Inclination (degrees)
% 18-25	344.7760	Right Ascension of Ascending Node (degrees)
% 27-33	0007976	Eccentricity (decimal point assumed)
% 35-42	126.2523	Argument of Perigee (degrees)
% 44-51	325.9359	Mean Anomaly (degrees)
% 53-63	15.70406856	Mean Motion (revolutions/day)
% 64-68	32890	Revolution Number at Epoch 
inum = 1;
while 1
    % read first line
    tline = fgetl(fid);
    if ~ischar(tline), break, end
    epochY = str2double(tline(19:20));                             % Epoch year
    epochD = str2double(tline(21:32));                             % Epoch day
    epoch = epochY * 365.25 + epochD;                           % Epoch (day)

    dv = datevec(epoch); % date vector as [Y, M, D, H, MN, S]
    dv = round(dv);
    Y = dv(1) + 2000;
    Mo = dv(2);
    D = dv(3);
    H = dv(4);
    MN = dv(5);
    SC = dv(6);
    
    Mjd0 = time_variables.Mjday(Y, Mo, D, H, MN, SC);
    UTC_initial = [Y, Mo, D, H, MN, SC];
    assignin('base','UTC_initial',UTC_initial)
    assignin('base','MJD_UTC0',Mjd0)
    month_ini = month2char(Mo);
    
    assignin('base','t0',append(num2str(D),' ',month_ini,' ',num2str(Y),' ',num2str(H),':',num2str(MN),':',num2str(SC)));
    
    Bstar = str2double(strcat('0.',tline(55:59)))*(10^(str2double(tline(60:61))));

    % read second line
    tline = fgetl(fid);
    if ~ischar(tline), break, end
    inc = str2double(tline(9:16))*pi/180;                                 % Orbit Inclination (degrees)
    RAAN = str2double(tline(18:25))*pi/180;                               % Right Ascension of Ascending Node (degrees)
    e = str2double(strcat('0.',tline(27:33)));                   % Eccentricity
    w = str2double(tline(35:42))*pi/180;                                  % Argument of Perigee (degrees)
    M = str2double(tline(44:51));                                  % Mean Anomaly (degrees)
    a = ( mu/(str2double(tline(53:63))*2*pi/86400)^2 )^(1/3);    % semi major axis
    e = e;
    rNo = str2double(tline(64:68));                                % Revolution Number at Epoch 
    M = M*pi/180;
    E       = M+ e*sin(M+e*sin(M+ e*sin(M+ e*sin(M+e*sin(M+ e*sin(M+ e*sin(M) + e*sin(M)))))));
    omecosE         = 1.0-e*cos(E);
    sintano         = sqrt(1-e^2)*sin(E)/omecosE;
    costano         = (cos(E)-e)/omecosE;
    tano    = atan2(sintano, costano);

    tano    = mod(tano, 2*pi);
    inum = inum + 1;
end

B = Bstar*2/((2.461e-5)*6378.137);
fclose(fid);

end

