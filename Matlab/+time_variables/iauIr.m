function r = iauIr(r)
%  - - - - - -
%   i a u I r
%  - - - - - -
%
%  Initialize an r-matrix to the identity matrix.
%
%  This function is part of the International Astronomical Union's
%  SOFA (Standards Of Fundamental Astronomy) software collection.
%
%  Status:  vector/matrix support function.
%
%  Returned:
%     r                 r-matrix
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
© 2025 Yazan Chihabi
%}

r(1,1) = 1.0;
r(1,2) = 0.0;
r(1,3) = 0.0;
r(2,1) = 0.0;
r(2,2) = 1.0;
r(2,3) = 0.0;
r(3,1) = 0.0;
r(3,2) = 0.0;
r(3,3) = 1.0;

end
