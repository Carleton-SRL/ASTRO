function state_post = RK4_step(t0,state_pre,dt,fcn)
%RK4_STEP Fixed-step fourth-order Runge-Kutta integrator.
%   state_post = dynamics.RK4_step(t0,state_pre,dt,fcn) advances the state
%   using fcn(t,state). This helper is intended for real-time/HIL propagation
%   where repeatedly starting ode45 inside the main simulation loop is costly.
%{
© 2025 Yazan Chihabi
Performance patch: fixed-step propagator helper.
%}

K1 = fcn(t0, state_pre);
K2 = fcn(t0 + 0.5*dt, state_pre + 0.5*dt*K1);
K3 = fcn(t0 + 0.5*dt, state_pre + 0.5*dt*K2);
K4 = fcn(t0 + dt,       state_pre + dt*K3);

state_post = state_pre + (dt/6)*(K1 + 2*K2 + 2*K3 + K4);
end
