function [range,angle] = Model(targetstates,chaserstates,RADAR_params,ConstantParameters)
%{
© 2025 Yazan Chihabi
%}
C_HI = Rotations.CHI(chaserstates);
RelPos = C_HI*(targetstates(1:3)-chaserstates(1:3));
if all(RelPos == 0)
    RNG = 0;
    ANG = [0;0];
else
    [RNG,ANG] = rangeangle(RelPos);
end

error = SensorModels.RADAR.noise_model(RNG,RADAR_params,ConstantParameters);

range = RNG + error(1);
Az = ANG(1) + error(2);
El = ANG(2) + error(3);
angle = [Az;El];

end