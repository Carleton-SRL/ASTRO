function EKF_est = correction(EKF_priori,y,R)
% EKF_GPS correction phase
% Copyright Yazan Chihabi 2024

states_priori = EKF_priori(1:6);

n = length(states_priori);
P_priori = zeros(n,n);
for i = 1:n
    P_priori(:,i) = EKF_priori(i*n+1:(i+1)*n);
end

H = eye(6,6);

y_est = H*states_priori;

error = y - y_est;

Pr = H*P_priori*H'+R;

Pr_inv = Alg_Math.Cholesky.Chol_Inv(Pr);  

K = (P_priori*H')*Pr_inv;

states_post  = states_priori + K*error;

P_post = (eye(6,6)-K*H)*P_priori*(eye(6,6)-K*H)' + K*R*K';


EKF_est = [states_post;P_post(:)];

end