function C = ECI2ECEF_Rot(GMT)
%{
© 2025 Yazan Chihabi
%}
C = [cos(GMT) sin(GMT) 0; -sin(GMT) cos(GMT) 0; 0 0 1];

end