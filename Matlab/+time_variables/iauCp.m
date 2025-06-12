function c = iauCp(p)
%  - - - - - -
%   i a u C p
%  - - - - - -
%
%  Copy a p-vector.
%
%  This function is part of the International Astronomical Union's
%  SOFA (Standards Of Fundamental Astronomy) software collection.
%
%  Status:  vector/matrix support function.
%
%  Given:
%     p             p-vector to be copied
%
%  Returned:
%     c             copy
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%{
© 2025 Yazan Chihabi
%}
c = [0,0,0];
c(1) = p(1);
c(2) = p(2);
c(3) = p(3);
end
