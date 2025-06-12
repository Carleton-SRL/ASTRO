function [r_fi,v_fi,a_fi,jerk_fi] = QuantizeStates(r,v,a,jerk)
%{
© 2025 Yazan Chihabi
%}
%% Quantize position, velocity, acceleration and jerk to fixed-point
    r_fi = int32(r.*10^2); % Position
    v_fi = int32(v.*10^5); % Velocity
    a_fi = int16(a.*10^2); % Acceleration
    jerk_fi = int16(jerk.*10^2); % Jerk
end