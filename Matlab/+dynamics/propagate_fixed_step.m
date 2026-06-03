function states_out = propagate_fixed_step(t_grid,state_ini,fcn)
%PROPAGATE_FIXED_STEP Propagate over a supplied time grid with RK4.
%   states_out is returned as nStates x numel(t_grid), matching the transposed
%   form commonly used after ode45 in this project.
%{
© 2025 Yazan Chihabi
Performance patch: fixed-step propagation helper.
%}

state_ini = state_ini(:);
n = numel(state_ini);
N = numel(t_grid);
states_out = zeros(n,N);
states_out(:,1) = state_ini;

for kk = 2:N
    h = t_grid(kk) - t_grid(kk-1);
    states_out(:,kk) = dynamics.RK4_step(t_grid(kk-1),states_out(:,kk-1),h,fcn);
end
end
