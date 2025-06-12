%{
© 2025 Yazan Chihabi
%}
%% Initialize Navigation
disp('Initializing navigation algorithms...')
[oe_moon,tanom,oe_sun,tanos] = dynamics.OE.SunMoon_OE(t,MJD_UTC0,eopdata,ConstantParameters);
disp('Navigation algorithms initialized')