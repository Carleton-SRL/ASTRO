function [TargetStates_Est,ChaserStates_Est,EKF_post] = estimator(EKF_pre, u, RADAR, ...
    Chaser_GPS, GPS_Status, Chaser_TLE, Chaser_TLE_flag, dt, Node_Time, Q, R, ConstantParameters)
% EKF_RADAR State Estimator
% Copyright Yazan Chihabi 2024


if GPS_Status
    measurements = [RADAR;Chaser_GPS];
else
    measurements = [RADAR;Chaser_TLE];
end

range = measurements(1);
az = measurements(2)*ConstantParameters.Rad;
el = measurements(3)*ConstantParameters.Rad;
y = [range*cos(el)*cos(az);range*cos(el)*sin(az);range*sin(el);measurements(4:9)];

if Node_Time<dt
    dt = 0;
end

[EKF_priori] = Navigation.EKF_RADAR.propagation(EKF_pre, u, dt, Q, ConstantParameters.mu_Earth);

EKF_post = Navigation.EKF_RADAR.correction(EKF_priori,y,GPS_Status,Chaser_TLE_flag,R);

TargetStates_Est = EKF_post(1:6);
ChaserStates_Est = EKF_post(7:12);


end