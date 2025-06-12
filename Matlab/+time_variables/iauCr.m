function c = iauCr(r)
%  - - - - - -
%   i a u C r
%  - - - - - -
%
%  Copy an r-matrix.
%
%  This function is part of the International Astronomical Union's
%  SOFA (Standards Of Fundamental Astronomy) software collection.
%
%  Status:  vector/matrix support function.
%
%  Given:
%     r            r-matrix to be copied
%
%  Returned:
%   char           copy
%
%  Called:
%     iauCp        copy p-vector
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
© 2025 Yazan Chihabi
%}

c(1,:) = iauCp(r(1,:));
c(2,:) = iauCp(r(2,:));
c(3,:) = iauCp(r(3,:));
end
