%{
© 2025 Yazan Chihabi
%}
mkdir(['Results/',currDate],'GPS_Results')
GPS_folder = [pwd,'/Results/',currDate,'/GPS_Results'];
%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPSvsActual_position'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
subplot(3,1,1)
plot(N_Orbits,StateVars_Chaser(1,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(1,:),'r-.')
ylabel('r_x (km)')
legend('Truth','GPS', 'Location','northeast')
grid on
subplot(3,1,2)
plot(N_Orbits,StateVars_Chaser(2,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(2,:),'r-.')
ylabel('r_y (km)')
grid on
subplot(3,1,3)
plot(N_Orbits,StateVars_Chaser(3,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(3,:),'r-.')
xlabel('Number of Orbits')
ylabel('r_z (km)')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all

%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPSvsActual_velocity'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.
%%
figure
subplot(3,1,1)
plot(N_Orbits,StateVars_Chaser(4,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(4,:),'r-.')
ylabel('v_x (km/s)')
legend('Truth','GPS', 'Location','northeast')
grid on
subplot(3,1,2)
plot(N_Orbits,StateVars_Chaser(5,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(5,:),'r-.')
ylabel('v_y (km/s)')
grid on
subplot(3,1,3)
plot(N_Orbits,StateVars_Chaser(6,:),'k-',N_Orbits,StateVars_Chaser_GPS_Receiver(6,:),'r-.')
xlabel('Number of Orbits')
ylabel('v_z (km/s)')
grid on
%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all

%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPS_Error_position'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
subplot(4,1,1)
plot(N_Orbits,GPS_Error(1,:),'k-')
ylabel('e_{r_x} (km)')
grid on
subplot(4,1,2)
plot(N_Orbits,GPS_Error(2,:),'k-')
ylabel('e_{r_y} (km)')
grid on
subplot(4,1,3)
plot(N_Orbits,GPS_Error(3,:),'k-')
ylabel('e_{r_z} (km)')
grid on
subplot(4,1,4)
plot(N_Orbits,GPS_Receiver_Status,'k-')
ylim([-1 2])
xlabel('Number of Orbits')
ylabel('GPS Solution')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all


%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPS_Error_position_histogram'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
subplot(1,3,1)
histogram(GPS_Error(1,:),'FaceColor','k')
xlabel('e_{r_x} (km)')
ylabel('Count')
grid on
subplot(1,3,2)
histogram(GPS_Error(2,:),'FaceColor','k')
xlabel('e_{r_y} (km)')
grid on
subplot(1,3,3)
histogram(GPS_Error(3,:),'FaceColor','k')
xlabel('e_{r_z} (km)')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all



%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPS_Error_velocity'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
subplot(4,1,1)
plot(N_Orbits,GPS_Error(4,:),'k-')
ylabel('e_{v_x} (km/s)')
grid on
subplot(4,1,2)
plot(N_Orbits,GPS_Error(5,:),'k-')
ylabel('e_{v_y} (km/s)')
grid on
subplot(4,1,3)
plot(N_Orbits,GPS_Error(6,:),'k-')
ylabel('e_{v_z} (km/s)')
grid on
subplot(4,1,4)
plot(N_Orbits,GPS_Receiver_Status,'k-')
ylim([-1 2])
xlabel('Number of Orbits')
ylabel('GPS Solution')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all


%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [GPS_folder,'/GPS_Error_velocity_histogram'];
% filename = [pwd,currDate,'/errornavchaser'];
% font change

% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
subplot(1,3,1)
histogram(GPS_Error(4,:),'FaceColor','k')
xlabel('e_{v_x} (km)')
ylabel('Count')
grid on
subplot(1,3,2)
histogram(GPS_Error(5,:),'FaceColor','k')
xlabel('e_{v_y} (km)')
grid on
subplot(1,3,3)
histogram(GPS_Error(6,:),'FaceColor','k')
xlabel('e_{v_z} (km)')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't(1:floor(length(t)/2)) know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    exportgraphics(gcf,[filename,'.pdf'],"Resolution",700)
end

close all
