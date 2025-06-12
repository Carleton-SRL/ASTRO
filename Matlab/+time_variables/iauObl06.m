function eps0 = iauObl06(date1, date2, ConstantParameters)
%{
© 2025 Yazan Chihabi
%}



% Interval between fundamental date J2000.0 and given date (JC).
t = ((date1 - ConstantParameters.DJ00) + date2) / ConstantParameters.DJC;

% Mean obliquity.
eps0 = (84381.406     +...
       (-46.836769    +...
       ( -0.0001831   +...
       (  0.00200340  +...
       ( -0.000000576 +...
       ( -0.0000000434) * t) * t) * t) * t) * t) * ConstantParameters.DAS2R;
end
