%{
© 2025 Yazan Chihabi
%}
TLE_pos_std = 0.001;
TLE_vel_std = 0.000001;
TLE_Bcoeff_std = 0.0001;
TLE_std = [TLE_pos_std;TLE_vel_std;TLE_Bcoeff_std;TLE_Bcoeff_std];
TLE_update_rate = 3600;
TLE_prop = [oe2(1:5)';M2;tano2;BSRP_c;Bdrag_c];
TLE_prop_target = [oe1(1:5)';M1;tano1;BSRP_t;Bdrag_t];
TLE_update = false;