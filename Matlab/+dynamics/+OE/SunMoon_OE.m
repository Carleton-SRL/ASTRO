function [oe_moon,tanom,oe_sun,tanos] = SunMoon_OE(t,MJD_UTC0,eopdata,ConstantParameters)
%{
© 2025 Yazan Chihabi
%}
mu = ConstantParameters.mu_Earth;
mu_sun = ConstantParameters.mu_Sun;
mu_moon = ConstantParameters.mu_Moon;

% Julian Dates
JD = zeros(1,length(t));
for k=1:length(t)
    MJD_UTC = MJD_UTC0+t(k)/86400;
    [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = time_variables.IERS(eopdata,MJD_UTC,'l',ConstantParameters);
    [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = time_variables.timediff(UT1_UTC,TAI_UTC);

    JD(k) = MJD_UTC+2400000.5;
end


% Moon position and velocity in ECI, and Orbital elements
oe_sun = zeros(6,length(JD));
tanos = zeros(1,length(JD));
oe_moon = zeros(6,length(JD));
tanom = zeros(1,length(JD));
[pos,vel] = planetEphemeris(JD','Earth','Sun'); % replace with custom function
for i = 1:length(JD)
    [oe_sun(:,i),tanos(:,i)] = Rotations.ECI2oe(pos(i,:)',vel(i,:)',mu+mu_sun);
end
[pos,vel] = planetEphemeris(JD','Earth','Moon'); % replace with custom function
for i = 1:length(JD)
    [oe_moon(:,i),tanom(:,i)] = Rotations.ECI2oe(pos(i,:)',vel(i,:)',mu+mu_moon);
end

end