%{
© 2025 Yazan Chihabi
%}
mkdir(['Results/',currDate],'/Control_Results')
Control_folder = [pwd,'/Results/',currDate,'/Control_Results'];

%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [Control_folder,'/lvlhxy_ctl'];

% font change
set(0,'DefaultAxesFontName', 'Times New Roman') 


% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
% set(gca,'FontSize',15)
%set(gcf, 'Position', get(0, 'Screensize'));
% plot(y*1000,x*1000,'b--');
plot(RelativeStates_True(2,:)*1000,RelativeStates_True(1,:)*1000,'k-',RelativeStates_guidance(2,:).*1000,RelativeStates_guidance(1,:).*1000,'r-.');
axis([-200 200 -200 200]);
%set(gca,'FontSize',30,'FontName', 'Times')
xlabel('y [along-track] (m)')
ylabel('x [radial] (m)')
axis tight
legend('Actual', 'Desired', 'Location','northeast')
set(gca,'XDir','reverse')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    print(filename,'-dpdf','-r700');
end

close all


%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [Control_folder,'/lvlh_ctl'];

% font change
set(0,'DefaultAxesFontName', 'Times New Roman') 


% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure;
% set(gca,'FontSize',15)
%set(gcf, 'Position', get(0, 'Screensize'));
subplot(1,2,1)
% plot(y*1000,x*1000,'b--');
plot(RelativeStates_True(2,:)*1000,RelativeStates_True(1,:)*1000,'k-',RelativeStates_guidance(2,:).*1000,RelativeStates_guidance(1,:).*1000,'r-.')
axis([-200 200 -200 200]);
%set(gca,'FontSize',30,'FontName', 'Times')
xlabel('y [along-track] (m)')
ylabel('x [radial] (m)')
axis tight
legend('Actual','Desired', 'Location','northeast')
set(gca,'XDir','reverse')
grid on
subplot(1,2,2)
plot(RelativeStates_True(2,:)*1000,RelativeStates_True(3,:)*1000,'k-',RelativeStates_guidance(2,:).*1000,RelativeStates_guidance(3,:).*1000,'r-.');
axis([-200 200 -200 200]);
%set(gca,'FontSize',30,'FontName', 'Times')
xlabel('y [along-track] (m)')
ylabel('z [in-track] (m)')
axis tight
% legend('Actual Position', 'Desired', 'Location','northeast')
set(gca,'XDir','reverse')
grid on

%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    print(filename,'-dpdf','-r700');
end

close all


%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [Control_folder,'/error_ctl'];
% font change
set(0,'DefaultAxesFontName', 'Times New Roman') 


% size of the figure (in inches)
width = 10;  
height = 6;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure;
subplot(3,2,[1,3,5])
plot(N_Orbits,RelativeDistance_True,'k-',N_Orbits,RelativeDistance_guidance,'r-.');
%set(gca,'FontSize',30,'FontName', 'Times')
legend('True Distance','Desired', 'Location','northeast')
xlabel('Number of Orbits')
ylabel('Relative Distance (km)')
axis tight
subplot(3,2,2)
plot(N_Orbits,RelativeStates_guidance(1,:) - RelativeStates_True(1,:),'k-')
% ylim([-70 70])
ylabel('e_{\rho_x} (km)')
% xlabel('t (sec)')
% set(gca,'FontSize',15,'FontName', 'Times')
% set(gca,'XTick',[])
% axis tight
grid on
subplot(3,2,4)
plot(N_Orbits,RelativeStates_guidance(2,:) - RelativeStates_True(2,:),'k-')
% ylim([-20 20])
ylabel('e_{\rho_x} (km)')
% xlabel('t (sec)')
% set(gca,'FontSize',15,'FontName', 'Times')
% set(gca,'XTick',[])
% axis tight
grid on
subplot(3,2,6)
plot(N_Orbits,RelativeStates_guidance(3,:) - RelativeStates_True(3,:),'k-')
% ylim([-0.6 0.6])
xlabel('Number of Orbits')
ylabel('e_{\rho_z} (km)')
% set(gca,'FontSize',15,'FontName', 'Times')
% axis tight
grid on


%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    print(filename,'-dpdf','-r700');
end

close all


%% Print Settings
% The user must specify the appropriate settings for their pdf print
close all

% print figure to pdf? 1 = yes, 0 = no
print_figs = 1;

% file name (it will be saved to the folder you are working in)
filename = [Control_folder,'/ctl'];

% font change
set(0,'DefaultAxesFontName', 'Times New Roman') 


% size of the figure (in inches)
width = 7;  
height = 4;

% This section is where the user must generate their own plots within
% MATLAB using their own data. Since the formatting for these plots is
% extensively covered in the online documentation, details on how to do
% this will not be covered here. This example generates a quad plot.

%%
figure
title('Control Accelerations (LVLH)')
subplot(3,1,1)
plot(N_Orbits,Control_Chaser(1,:).*1000,'k-')
ylabel('x (m/s^2)')
% set(gca,'FontSize',20,'FontName', 'Times')
subplot(3,1,2)
plot(N_Orbits,Control_Chaser(2,:).*1000,'k-')
ylabel('y (m/s^2)')
% set(gca,'FontSize',20,'FontName', 'Times')
subplot(3,1,3)
plot(N_Orbits,Control_Chaser(3,:).*1000,'k-')
xlabel('Number of Orbits')
ylabel('z (m/s^2)')
% set(gca,'FontSize',20,'FontName', 'Times')
grid on


%% Saving figure to pdf
% This is where the magic happens!

% This block of code positions and crops the "paper" that MATLAB prints the
% pdf onto to the height and width specified earlier. It would be wise not
% to alter this if you don't know what you are doing!
pos = get(gcf, 'Position');		
set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); 
movegui('center');
set(gcf, 'Paperposition', [0 0 width height])	
set(gcf,'papersize',[width height])		
set(gcf,'renderer','Painters')

% This section prints the plot to a pdf to a resolution of 700 DPi.
% This can be adjusted as required
if print_figs == 1
    print(filename,'-dpdf','-r700');
end

close all