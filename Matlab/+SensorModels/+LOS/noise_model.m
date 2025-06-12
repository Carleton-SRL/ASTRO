function noise = noise_model(std)
%{
© 2025 Yazan Chihabi
%}
noise = [0;0;0];
noise(1) = std(1)*rand;
noise(2) = std(2)*rand;
noise(3) = std(3)*rand;

end