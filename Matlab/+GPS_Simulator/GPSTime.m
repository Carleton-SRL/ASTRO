function [weeks,secs] = GPSTime(UTC_initial)
%{
© 2025 Yazan Chihabi
%}
t = datetime(UTC_initial);
GPS0 = datetime(1980,1,6,0,0,0,'TimeZone','UTCLeapSeconds');
tLS = t; 
tLS.TimeZone = 'UTCLeapSeconds';
deltaT = tLS - GPS0; 
deltaT.Format = 's';
weeks = floor(seconds(deltaT)/(7*86400));
secs = seconds(rem(deltaT,seconds(7*86400)));


end