function c = binomialcoeff(n,k)
%{
© 2025 Yazan Chihabi
%}
c = Alg_Math.factorialm(n)/(Alg_Math.factorialm(n-k)*Alg_Math.factorialm(k));
end