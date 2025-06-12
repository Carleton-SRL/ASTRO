function EKF_est = correction(EKF_priori,y,GPS_Status,Chaser_TLE_flag,R)
% EKF_RADAR correction phase
% Copyright Yazan Chihabi 2024

states_priori = EKF_priori(1:12);
C_HI_chaser  =  Rotations.CHI(states_priori(7:12));

n = length(states_priori);
P_priori = zeros(n,n);
for i = 1:n
    P_priori(:,i) = EKF_priori(i*n+1:(i+1)*n);
end

H = zeros(9,n);

H(1:3,1:3) = C_HI_chaser*eye(3,3);
H(1:3,7:9) = -H(1:3,1:3);
H(4:9,7:12) = eye(6,6);

% if GPS_Status || Chaser_TLE_flag
%     y_est = H*states_priori;
% 
%     error = y - y_est;
% 
%     Pr = H*P_priori*H'+R;
% 
%     Pr_inv = Alg_Math.Cholesky.Chol_Inv(Pr);  
% 
%     K = (P_priori*H')*Pr_inv;
% 
%     states_post  = states_priori + K*error;
% 
%     P_post = (eye(12)-K*H)*P_priori*(eye(12)-K*H)' + K*R*K';
% else
%     H_red = H(1:3,:);
%     R_red = R(1:3,1:3);
%     y_est = H_red*states_priori;
% 
%     error_red = y(1:3) - y_est;
% 
%     Pr_red = H_red*P_priori*H_red'+R_red;
% 
%     Pr_red_inv = Alg_Math.Cholesky.Chol_Inv(Pr_red);  
% 
%     K_red = (P_priori*H_red')*Pr_red_inv;
% 
%     states_post  = states_priori + K_red*error_red;
% 
%     P_post = (eye(12)-K_red*H_red)*P_priori*(eye(12)-K_red*H_red)' + K_red*R_red*K_red';
% end

y_est = H*states_priori;

error = y - y_est;

Pr = H*P_priori*H'+R;

Pr_inv = Alg_Math.Cholesky.Chol_Inv(Pr);  

K = (P_priori*H')*Pr_inv;

states_post  = states_priori + K*error;

P_post = (eye(12)-K*H)*P_priori*(eye(12)-K*H)' + K*R*K';

EKF_est = [states_post;P_post(:)];

end