function [TargetStates_Est,EKF_post] = estimator(EKF_pre, measurements, ...
    ChaserStates, dt, Node_Time, Q, R, ConstantParameters)
% EKF_RADAR State Estimator
% Copyright Yazan Chihabi 2024

C_HI_chaser  =  Rotations.CHI(ChaserStates);

range = measurements(1);
az = measurements(2)*ConstantParameters.Rad;
el = measurements(3)*ConstantParameters.Rad;
y = C_HI_chaser'*[range*cos(el)*cos(az);range*cos(el)*sin(az);range*sin(el)];
y = ChaserStates(1:3) + y;

if Node_Time<dt
    dt = 0;
end

[EKF_priori] = Navigation.EKF_RADAR_Reduced.propagation(EKF_pre, dt, Q, ConstantParameters.mu_Earth);

EKF_post = Navigation.EKF_RADAR_Reduced.correction(EKF_priori,y,R);

TargetStates_Est = EKF_post(1:6);


end