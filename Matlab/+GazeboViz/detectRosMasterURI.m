function masterURI = detectRosMasterURI()
%DETECTROSMASTERURI Detect ROS master URI for WSL/Ubuntu/Gazebo.
%
% Priority:
%   1. MATLAB environment variable ROS_MASTER_URI, if set
%   2. Windows MATLAB: `wsl hostname -I`
%   3. Linux MATLAB: `hostname -I`
%   4. localhost fallback

existing = getenv('ROS_MASTER_URI');
if ~isempty(existing)
    masterURI = existing;
    return;
end

ip = '';
if ispc
    [status,out] = system('wsl hostname -I');
else
    [status,out] = system('hostname -I');
end

if status == 0
    parts = strsplit(strtrim(out));
    if ~isempty(parts)
        ip = strtrim(parts{1});
    end
end

if isempty(ip)
    ip = 'localhost';
end

masterURI = ['http://' ip ':11311'];
end
