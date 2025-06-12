%{
© 2025 Yazan Chihabi
%}
P_rt   = 2; % radar transmit power
PC_ratio    = 1000; % pulse compression ratio
G_rt   = 35; % transmitter gain (antenna)
sigma_rcs = 10; % target radar cross section
A_er   = 2; % radar receive antenna effective aperature area
k_Boltz     = 1.38e-23; % boltzmann constant
T_sys   = 298; % radar system noise temp
RADAR_Losses     = 5; % other system losses
RADAR_Bandwidth = 1e6; % radar bandwidth
RADAR_BeamWidth = 2; % radar beamwidth (deg)

RADAR_fcn = 10*log10(P_rt*sigma_rcs*A_er*PC_ratio) + G_rt - (10*log10(((4*pi)^2)*RADAR_Bandwidth*k_Boltz*T_sys) + RADAR_Losses);
RADAR_fcn = (10^(RADAR_fcn/10))*1000;
RADAR_params = [RADAR_fcn;RADAR_Bandwidth;RADAR_BeamWidth];
