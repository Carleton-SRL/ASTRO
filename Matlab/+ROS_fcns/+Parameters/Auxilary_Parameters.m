function AuxilaryParameters = Auxilary_Parameters()
%{
© 2025 Yazan Chihabi
%}

AuxilaryParameters.mass1 = rosparam("get","AuxilaryParameters/mass1");
AuxilaryParameters.Cr1 = rosparam("get","AuxilaryParameters/Cr1");
AuxilaryParameters.Cd1 = rosparam("get","AuxilaryParameters/Cd1");
AuxilaryParameters.area_solar1 = rosparam("get","AuxilaryParameters/area_solar1");
AuxilaryParameters.area_drag1 = rosparam("get","AuxilaryParameters/area_drag1");
AuxilaryParameters.mass2 = rosparam("get","AuxilaryParameters/mass2");
AuxilaryParameters.Cr2 = rosparam("get","AuxilaryParameters/Cr2");
AuxilaryParameters.Cd2 = rosparam("get","AuxilaryParameters/Cd2");
AuxilaryParameters.area_solar2 = rosparam("get","AuxilaryParameters/area_solar2");
AuxilaryParameters.area_drag2 = rosparam("get","AuxilaryParameters/area_drag2");

end