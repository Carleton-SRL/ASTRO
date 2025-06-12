function load_all_mat_files(folderPath)
%{
© 2025 Yazan Chihabi
%} 
% Ensure folder exists
    if ~isfolder(folderPath)
        error('Specified folder does not exist.');
    end

    % Get list of all .mat files
    matFiles = dir(fullfile(folderPath, '*.mat'));

    % Load each .mat file into the caller workspace
    for i = 1:length(matFiles)
        filePath = fullfile(folderPath, matFiles(i).name);
        fprintf('Loading %s...\n', filePath);
        vars = load(filePath);  % Load into a struct
        varNames = fieldnames(vars);
        for j = 1:length(varNames)
            assignin('base', varNames{j}, vars.(varNames{j}));
        end
    end
end
