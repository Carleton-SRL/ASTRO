function w = iauAnp(a, ConstantParameters)
%   - - - - - - -
%    i a u A n p
%   - - - - - - -
% 
%   Normalize angle into the range 0 <= a < 2pi.
% 
%   This function is part of the International Astronomical Union's
%   SOFA (Standards Of Fundamental Astronomy) software collection.
% 
%   Status:  vector/matrix support function.
% 
%   Given:
%      a        double     angle (radians)
% 
%   Returned (function value):
%               double     angle in range 0-2pi
% 
% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
© 2025 Yazan Chihabi
%}

w = mod(a, ConstantParameters.D2PI);
if (w < 0)
    w = w + ConstantParameters.D2PI;
end

end
