function [States_Est,EKF_post] = estimator(EKF_pre,u, ...
    Chaser_GPS, GPS_Status, Chaser_TLE, Chaser_TLE_flag, dt, Node_Time, Q, R, ...
    ConstantParameters)
% EKF_GPS State Estimator
% Copyright Yazan Chihabi 2024

if Chaser_TLE_flag
    measurements = Chaser_TLE;
else
    measurements = Chaser_GPS;
end

if Node_Time<dt
    dt = 0;
end

[EKF_priori] = Navigation.EKF_GPS.propagation(EKF_pre, u, dt, Q, ConstantParameters.mu_Earth);

if GPS_Status || Chaser_TLE_flag
    EKF_post = Navigation.EKF_GPS.correction(EKF_priori,measurements,R);
else
    EKF_post = EKF_priori;
end

States_Est = EKF_post(1:6);


end