function state_post = RK_int(state_pre,dt,fcn)
%{
© 2025 Yazan Chihabi
%}
K1 = fcn(state_pre)*dt;
K2 = fcn(state_pre + K1/3)*dt;
K3 = fcn(state_pre + (K1+K2)/6)*dt;
K4 = fcn(state_pre + (K1+3*K3)/8)*dt;
K5 = fcn(state_pre + (K1+4*K4-3*K3)/2)*dt;

state_post  	= state_pre+(K1+4*K4+K5)/6;
end