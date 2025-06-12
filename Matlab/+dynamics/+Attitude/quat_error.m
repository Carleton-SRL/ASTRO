function q_error  = quat_error(Attitude_Nav,qd)

%{
© 2025 Yazan Chihabi
%}
%% Quaternion Error
q_Nav = Attitude_Nav(1:4);
% q_Nav = NormalizeQuaternion(q_Nav);

qm = [ qd(4), qd(3),-qd(2),-qd(1);
      -qd(3), qd(4), qd(1),-qd(2);
       qd(2),-qd(1), qd(4),-qd(3);
       qd(1), qd(2), qd(3), qd(4)];
   
q_error = (qm * q_Nav);

% q_error = NormalizeQuaternion(q_error); % normalizing and ensuring q(4) is positive

if isnan(q_error)
    q_error = [0;0;0;1];
end


end