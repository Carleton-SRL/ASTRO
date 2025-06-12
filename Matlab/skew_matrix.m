function [ matrix ] = skew_matrix( x )
% Calculates the the skew symatrix matrix of a 3 dimensional vector x
% Copyright Yazan Chihabi 2018

matrix = [0 -x(3) x(2) ; x(3) 0 -x(1) ; -x(2) x(1) 0 ];



end

