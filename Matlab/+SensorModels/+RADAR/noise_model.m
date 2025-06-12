function noise = noise_model(R,RADAR_params,ConstantParameters)
%{
© 2025 Yazan Chihabi
%}
RADAR_fcn = RADAR_params(1);
B         = RADAR_params(2);
ChaserRadarBeamWidth = RADAR_params(3);
SNR = RADAR_fcn/(R^4);
% SNR = RADAR_fcn - 10*log10(R^4);
% SNR = 10^(SNR/10);
RADAR_sigmaRN = ConstantParameters.c_light/(2*B*sqrt(2*SNR));
RADAR_sigmaAN = ChaserRadarBeamWidth/(1.6*sqrt(2*SNR));
noise = [0;0;0];
noise(1) = RADAR_sigmaRN*rand;
noise(2) = RADAR_sigmaAN*rand;
noise(3) = RADAR_sigmaAN*rand;

end