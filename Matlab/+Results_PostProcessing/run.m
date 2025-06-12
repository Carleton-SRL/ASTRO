%{
© 2025 Yazan Chihabi
%}

GPS_Error = zeros(6,length(t));
RelativeStates_True = zeros(6,length(t));
RelativeDistance_True = zeros(1,length(t));
RelativeDistance_est = zeros(1,length(t));
RelativeDistance_guidance = zeros(1,length(t));



for i = 1:length(t)
    if GPS_Receiver_Status(i) == 1
        GPS_Error(:,i) = StateVars_Chaser_GPS_Receiver(:,i) - StateVars_Chaser(1:6,i);
    end

    C_HI  =  Rotations.CHI(StateVars_Target(:,i));
    RelativePosition_True = C_HI*(StateVars_Chaser(1:3,i) - StateVars_Target(1:3,i));
    rTarget = sqrt(StateVars_Target(1,i)^2 + StateVars_Target(2,i)^2 + StateVars_Target(3,i)^2);
    w_HI = skew_matrix(StateVars_Target(1:3,i))*StateVars_Target(4:6,i)/(rTarget^2);
    RelativeVelocity_True = C_HI*(StateVars_Chaser(4:6,i) - StateVars_Target(4:6,i)) - (skew_matrix(w_HI)*RelativePosition_True);
    RelativeStates_True(:,i) = [RelativePosition_True;RelativeVelocity_True];
    RelativeDistance_True(i) = norm(RelativePosition_True);
    RelativeDistance_est(i) = norm(RelativeStates_est(1:3,i));
    RelativeDistance_guidance(i) = norm(RelativeStates_guidance(1:3,i));
end

RelativeDistance_guidance(1:2) = RelativeDistance_True(1:2);
RelativeDistance_est(1:2) = RelativeDistance_True(1:2);
RelativeStates_est(:,1:2) = RelativeStates_True(:,1:2);
RelativeStates_guidance(:,1:2) = RelativeStates_True(:,1:2);
GPS_Error(:,1:2) = zeros(6,2);

RelativeStates_Error = RelativeStates_True - RelativeStates_est;

GPS_TimeStamps_diff = GPS_TimeStamps_Simulator - [GPS_TimeStamps_Receiver(1,:);GPS_TimeStamps_Receiver(2,:).*1000];

GPS_Signal_Fix_Percent  = sum(GPS_Receiver_Status)/length(GPS_Receiver_Status)*100;
GPS_Signal_Loss_Percent = 100 - GPS_Signal_Fix_Percent;

N_Orbits = t./T1;

disp(['GPS Signal Loss: ',num2str(GPS_Signal_Loss_Percent),' %'])
disp('Saving data...')
currDate = strrep(datestr(datetime, 'yyyy-mm-dd_HH-MM-SS'), ':', '_');

% Prompt user to input a folder name 
saveFolder = input('Enter folder name to save results (press Enter for default): ', 's');
% Set up base folder path
if ~isempty(saveFolder)
    filepath = fullfile('Results', saveFolder, currDate);
else
    filepath = fullfile('Results', currDate);
end

% Create full directory path including 'data' subfolder
datapath = fullfile(filepath, 'data');
if ~exist(datapath, 'dir')
    mkdir(datapath);
end

% Get all variables in the current workspace
vars = whos;

% Save each variable individually
for i = 1:length(vars)
    varName = vars(i).name;
    varData = eval(varName);  % Get variable content
    save(fullfile(datapath, [varName '.mat']), varName);
end
disp(['Data saved to: Results\',currDate])


%% Figures
disp('Plotting data...')

set(0,'DefaultAxesFontName', 'Times New Roman')
set(0, 'DefaultLineLineWidth', 1.5);
set(0,'defaultAxesFontSize',16)

if hardware_flags(3)
    Results_PostProcessing.GPS
end


if hardware_flags(1) && GNC_flags(1) && ((Sensor_flags(4) && hardware_flags(2) && hardware_flags(3)) || Sensor_flags(3))
    Results_PostProcessing.EKF_GPS
end


if hardware_flags(1) && Sensor_flags(2)
    Results_PostProcessing.EKF_Relative
end

if hardware_flags(1) && Sensor_flags(2)
    Results_PostProcessing.Control
end

disp('Plotting Complete')
