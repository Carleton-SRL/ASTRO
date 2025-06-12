function [inertiaMatrix_Chaser,inertiaMatrix_Chaser_inv] = Inertia_Properties()
%{
© 2025 Yazan Chihabi
%}
inertiaMatrix_Chaser = zeros(3,3);
inertiaMatrix_Chaser(1,1) = rosparam("get","ChaserProperties/inertia/i11");
inertiaMatrix_Chaser(1,2) = rosparam("get","ChaserProperties/inertia/i12");
inertiaMatrix_Chaser(1,3) = rosparam("get","ChaserProperties/inertia/i13");
inertiaMatrix_Chaser(2,1) = rosparam("get","ChaserProperties/inertia/i21");
inertiaMatrix_Chaser(2,2) = rosparam("get","ChaserProperties/inertia/i22");
inertiaMatrix_Chaser(2,3) = rosparam("get","ChaserProperties/inertia/i23");
inertiaMatrix_Chaser(3,1) = rosparam("get","ChaserProperties/inertia/i31");
inertiaMatrix_Chaser(3,2) = rosparam("get","ChaserProperties/inertia/i32");
inertiaMatrix_Chaser(3,3) = rosparam("get","ChaserProperties/inertia/i33");

inertiaMatrix_Chaser_inv = zeros(3,3);
inertiaMatrix_Chaser_inv(1,1) = rosparam("get","ChaserProperties/inertia_inv/i11");
inertiaMatrix_Chaser_inv(1,2) = rosparam("get","ChaserProperties/inertia_inv/i12");
inertiaMatrix_Chaser_inv(1,3) = rosparam("get","ChaserProperties/inertia_inv/i13");
inertiaMatrix_Chaser_inv(2,1) = rosparam("get","ChaserProperties/inertia_inv/i21");
inertiaMatrix_Chaser_inv(2,2) = rosparam("get","ChaserProperties/inertia_inv/i22");
inertiaMatrix_Chaser_inv(2,3) = rosparam("get","ChaserProperties/inertia_inv/i23");
inertiaMatrix_Chaser_inv(3,1) = rosparam("get","ChaserProperties/inertia_inv/i31");
inertiaMatrix_Chaser_inv(3,2) = rosparam("get","ChaserProperties/inertia_inv/i32");
inertiaMatrix_Chaser_inv(3,3) = rosparam("get","ChaserProperties/inertia_inv/i33");

end