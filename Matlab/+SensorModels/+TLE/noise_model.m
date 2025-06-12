function noise = noise_model(std)
%{
© 2025 Yazan Chihabi
%}
noise = rand([8,1]);
noise(1:3) = std(1).*noise(1:3);
noise(4:6) = std(2).*noise(4:6);
noise(7)   = std(3).*noise(7);
noise(8)   = std(4).*noise(8);

end