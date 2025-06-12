function invA = Chol_Inv(A)
    %{
    © 2025 Yazan Chihabi
    %}
    % A must be positive definite and symmetric
    n = length( A );
    L = zeros( n, n );
    for i=1:n
       L(i, i) = sqrt(A(i, i) - L(i, :)*L(i, :)');
       for j=(i + 1):n
          L(j, i) = (A(j, i) - L(i,:)*L(j ,:)')/L(i, i);
       end
    end
    U = L';
    I = eye(length(A),length(A));
    X = zeros(length(A),length(A));
    for j = 1:length(A)
        b = I(:,j);
        S=size(U);
        m=S(1);
        if S(1)~=S(2)
            error('matrix mast be square')
        end
        x=zeros(1,m);
        x(1,m)=b(end)./U(m,m);
        %bacward substitution
        for k=m-1:-1:1


                x1=1/U(k,k).*(b(k)-sum(U(k,k+1:end).*x(k+1:end)));
                x(k)=x1;
        end
        
        X(:,j) = x';
    end
    
    invA = X*X';
end

