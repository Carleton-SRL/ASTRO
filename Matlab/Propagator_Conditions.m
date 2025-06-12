%{
© 2025 Yazan Chihabi
%}

StateVars = zeros(6,length(t));
StateVars_GPS_Receiver = zeros(6,length(t));
StateVars_Chaser_GPS_Receiver = zeros(6,length(t));
GPS_Receiver_Status = boolean(zeros(1,length(t)));
options=odeset('RelTol',1e-9,'AbsTol',1e-9);

r2_E_prop = r2_E_ini;
v2_E_prop = v2_E_ini;
a2_E_prop = a2_E_ini;

r2_E_prop_prev = r2_E_ini;
v2_E_prop_prev = v2_E_ini;
a2_E_prop_prev = a2_E_ini;

r2_I_prop_prev = r2_I_ini;
v2_I_prop_prev = v2_I_ini;
a2_I_prop_prev = a2_I_ini;

r2_I_prop = r2_I_ini;
v2_I_prop = v2_I_ini;
a2_I_prop = a2_I_ini;

r1_I_prop = r1_I_ini;
v1_I_prop = v1_I_ini;

StateVars_Target(:,1) = [r1_I_prop;v1_I_prop];
StateVars_Chaser(:,1) = [r2_I_prop;v2_I_prop];
X_prop = dynamics.simulator(0,[r2_I_prop;v2_I_prop], Cnm, Snm, ...
            ConstantParameters, AuxilaryParameters, MJD_initial, centralbody,  eopdata, ...
            PC, 2, [0;0;0]);

[oe_moon,tanom,oe_sun,tanos] = dynamics.OE.SunMoon_OE(t,MJD_UTC0,eopdata,ConstantParameters);