function TLE = Model(states,Bsrp,Bdrag,mu,std)
%{
© 2025 Yazan Chihabi
%}
r = states(1:3);
v = states(4:6);

noise = SensorModels.TLE.noise_model(std);

r = r + noise(1:3);
v = v + noise(4:6);
Bsrp = Bsrp + noise(7);
Bdrag = Bdrag + noise(8);

[oe,tano] = Rotations.ECI2oe(r,v,mu);

TLE = [oe;tano;Bsrp;Bdrag];

end