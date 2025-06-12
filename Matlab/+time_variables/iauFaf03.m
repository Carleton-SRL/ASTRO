function a = iauFaf03(t,ConstantParameters)
%{
© 2025 Yazan Chihabi
%}



% Mean longitude of the Moon minus that of the ascending node
% (IERS Conventions 2003).
a = mod( 335779.526232 + ...
        t * ( 1739527262.8478 + ...
        t * (       - 12.7512 + ...
        t * (        - 0.001037 + ...
        t * (          0.00000417 ) ) ) ), ConstantParameters.TURNAS ) * ConstantParameters.DAS2R;
end
