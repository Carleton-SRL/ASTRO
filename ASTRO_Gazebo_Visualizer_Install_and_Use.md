# ASTRO ROS1/Gazebo Visualizer — Installation and Usage Guide

This guide explains how to install and run the ASTRO spacecraft orbit visualizer using:

- Windows
- WSL2 Ubuntu 20.04
- ROS Noetic
- Gazebo 11
- MATLAB on Windows
- ASTRO MATLAB simulation publishing inertial spacecraft states

The visualizer runs in Gazebo inside WSL. MATLAB runs on Windows and connects to ROS through the WSL ROS master.

---

## 1. System architecture

```text
Windows
├── MATLAB
│   ├── initialization.m
│   ├── run_gazebo_visualizer.m
│   ├── publish_gazebo_demo_orbit.m
│   └── set_gazebo_lighting.m
│
└── WSL2 Ubuntu 20.04
    ├── ROS Noetic
    ├── Gazebo 11
    └── ASTRO Gazebo Visualizer
```

MATLAB publishes spacecraft state topics:

```text
/astro/target/state
/astro/chaser/state
```

The messages are `nav_msgs/Odometry` and represent inertial states:

```text
[pos; vel; quat; omega]
```

where:

```text
pos   = inertial position
vel   = inertial velocity
quat  = attitude quaternion, scalar-last [qx qy qz qw]
omega = angular velocity
```

Gazebo subscribes to these topics and updates the spacecraft models.

---

## 2. Install WSL2 Ubuntu 20.04

Open **PowerShell as Administrator** on Windows.

Run:

```powershell
wsl --install -d Ubuntu-20.04
```

Restart Windows if prompted.

Open **Ubuntu 20.04** from the Start Menu and create your Linux username and password.

Update Ubuntu:

```bash
sudo apt update
sudo apt upgrade -y
```

---

## 3. Install ROS Noetic and Gazebo 11

Inside Ubuntu/WSL, run:

```bash
sudo apt install curl gnupg2 lsb-release -y
```

Add the ROS signing key:

```bash
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc \
| sudo apt-key add -
```

Add the ROS Noetic repository:

```bash
echo "deb http://packages.ros.org/ros/ubuntu focal main" \
| sudo tee /etc/apt/sources.list.d/ros1.list
```

Update package lists:

```bash
sudo apt update
```

Install ROS Noetic Desktop Full, which includes Gazebo 11 and RViz:

```bash
sudo apt install ros-noetic-desktop-full -y
```

Install extra build tools:

```bash
sudo apt install python3-rosdep2 python3-catkin-tools python3-rosinstall python3-vcstool build-essential dos2unix -y
```

Source ROS automatically in every new terminal:

```bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

Verify ROS and Gazebo:

```bash
which roscore
which gazebo
```

Expected output:

```text
/opt/ros/noetic/bin/roscore
/usr/bin/gazebo
```

Optional Gazebo test:

```bash
gazebo
```

A Gazebo window should open. Close it before continuing.

---

## 4. Extract the ASTRO visualizer ZIP

Extract the latest ASTRO visualizer ZIP on Windows to:

```text
G:\Github\ASTRO
```

You should have:

```text
G:\Github\ASTRO\GazeboVisualizer
G:\Github\ASTRO\Matlab
```

Do not build directly from `/mnt/g/...` inside WSL. Windows-mounted drives can cause permission and CMake problems.

Instead, copy the visualizer into the Linux filesystem.

Inside Ubuntu/WSL:

```bash
rm -rf ~/ASTRO_GazeboVisualizer
cp -r /mnt/g/Github/ASTRO/GazeboVisualizer ~/ASTRO_GazeboVisualizer
cd ~/ASTRO_GazeboVisualizer
```

---

## 5. Build the Gazebo visualizer

Inside Ubuntu/WSL:

```bash
source /opt/ros/noetic/setup.bash
cd ~/ASTRO_GazeboVisualizer
bash build_gazebo_visualizer.sh
```

After a successful build, source the workspace:

```bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
```

Add the workspace to `.bashrc` so it loads automatically:

```bash
grep -qxF 'source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash' ~/.bashrc || \
echo 'source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash' >> ~/.bashrc
source ~/.bashrc
```

---

## 6. Avoid duplicate ROS package paths

If you previously sourced a workspace from the Windows-mounted folder, ROS may see duplicate packages.

Open `.bashrc`:

```bash
nano ~/.bashrc
```

Remove any line that contains:

```text
/mnt/g/Github/ASTRO/GazeboVisualizer
```

Keep only:

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
```

Reload:

```bash
source ~/.bashrc
```

---

## 7. Launch the visualizer in WSL

Open an Ubuntu/WSL terminal.

Run:

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
```

Launch the visualizer using the full launch file path:

```bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

Gazebo should open with:

- Earth
- Moon
- Sun visual model
- Target spacecraft
- Chaser spacecraft
- ROS state bridge
- Orbit marker engine
- Runtime lighting control node

Leave this terminal running.

---

## 8. Open a second WSL terminal

Open another WSL terminal using one of these methods:

### Option A: Windows Terminal

Open Windows Terminal, click the `+` menu, and select:

```text
Ubuntu-20.04
```

### Option B: Run command

Press `Win + R`, type:

```text
wsl
```

and press Enter.

### Option C: PowerShell

```powershell
wsl -d Ubuntu-20.04
```

In the second WSL terminal, get your WSL IP:

```bash
hostname -I
```

Example output:

```text
172.28.112.45 172.17.0.1
```

Use the first IP address for MATLAB if manual ROS initialization is needed.

---

## 9. MATLAB setup on Windows

Open MATLAB on Windows.

Go to the ASTRO MATLAB folder:

```matlab
cd('G:\Github\ASTRO\Matlab')
```

The updated project can automatically initialize ROS from the main initialization script.

Run:

```matlab
initialization
```

The initialization script should:

1. Detect or start MATLAB ROS connection.
2. Create Gazebo visualizer publishers.
3. Publish `/astro/target/state` and `/astro/chaser/state` during simulation.

If automatic ROS initialization fails, manually connect with the WSL IP:

```matlab
rosshutdown
rosinit('http://172.28.112.45:11311')
```

Replace `172.28.112.45` with your actual WSL IP.

Check topics:

```matlab
rostopic list
```

You should see topics such as:

```text
/astro/target/state
/astro/chaser/state
/astro/visualizer/lighting_mode
/astro/visualizer/sun_direction
```

---

## 10. Run the demo publisher

To test the visualizer without running the full ASTRO simulation, use:

```matlab
pubs = run_gazebo_visualizer();
publish_gazebo_demo_orbit
```

You should see the spacecraft move in Gazebo.

---

## 11. Run the full ASTRO simulation

Normal workflow:

```matlab
cd('G:\Github\ASTRO\Matlab')
initialization
```

or, if your project uses a separate entry point:

```matlab
RunSimulation
```

The visualizer expects MATLAB to publish:

```text
/astro/target/state
/astro/chaser/state
```

as `nav_msgs/Odometry`.

State convention:

```text
position           = inertial position
linear velocity    = inertial velocity
orientation        = quaternion [qx qy qz qw]
angular velocity   = omega
```

---

## 12. Lighting control from MATLAB

You can change the visualizer lighting while Gazebo is running.

Available modes:

```matlab
set_gazebo_lighting('day')
set_gazebo_lighting('dawn')
set_gazebo_lighting('eclipse')
set_gazebo_lighting('moonlight')
set_gazebo_lighting('soft')
set_gazebo_lighting('bright')
```

Examples:

```matlab
set_gazebo_lighting('day')
pause(2)
set_gazebo_lighting('eclipse')
pause(2)
set_gazebo_lighting('moonlight')
```

Custom Sun direction:

```matlab
set_gazebo_lighting([1; 0; -0.2])
```

Another example:

```matlab
set_gazebo_lighting([-0.3; 0.5; -1.0])
```

The direction vector does not need to be perfectly normalized. The lighting node will handle it.

---

## 13. Camera and view control

### Center view on chaser

In Gazebo:

1. Select the chaser model.
2. Press `F` to focus on it.
3. Right-click the chaser and choose `Follow` if available.

### Mouse controls

```text
Left mouse    = select
Middle mouse  = pan
Right mouse   = rotate view
Scroll wheel  = zoom
```

### Recommended view for rendezvous

For RPOD and formation flying, the most useful view is usually target-centered or LVLH-style, where:

```text
Target = near origin
Chaser = moving relative to target
```

This makes relative motion, docking, and inspection behavior easier to interpret.

---

## 14. Correct launch order

Use this order every time:

```text
1. Open WSL terminal.
2. Source ROS and the visualizer workspace.
3. Launch Gazebo visualizer.
4. Open MATLAB on Windows.
5. Run initialization.m.
6. Run the ASTRO simulation or demo publisher.
7. Change lighting using set_gazebo_lighting(...).
```

Exact commands:

### WSL terminal

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

### MATLAB

```matlab
cd('G:\Github\ASTRO\Matlab')
initialization
```

Optional demo:

```matlab
pubs = run_gazebo_visualizer();
publish_gazebo_demo_orbit
```

Optional lighting:

```matlab
set_gazebo_lighting('eclipse')
```

---

## 15. Troubleshooting

### Problem: `RLException: multiple files named orbit_visualizer.launch`

Cause: ROS sees two copies of the package.

Fix:

```bash
nano ~/.bashrc
```

Remove lines containing:

```text
/mnt/g/Github/ASTRO/GazeboVisualizer
```

Keep:

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
```

Then:

```bash
source ~/.bashrc
```

Launch using full path:

```bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

---

### Problem: `chmod: Operation not permitted`

Cause: You are trying to modify permissions on a Windows-mounted drive.

Fix: Copy the package into Linux home:

```bash
rm -rf ~/ASTRO_GazeboVisualizer
cp -r /mnt/g/Github/ASTRO/GazeboVisualizer ~/ASTRO_GazeboVisualizer
cd ~/ASTRO_GazeboVisualizer
```

Run scripts using `bash`:

```bash
bash build_gazebo_visualizer.sh
bash run_gazebo_visualizer.sh
```

---

### Problem: `rospy not found`

Install missing packages:

```bash
sudo apt update
sudo apt install ros-noetic-rospy ros-noetic-std-msgs ros-noetic-geometry-msgs ros-noetic-nav-msgs ros-noetic-visualization-msgs ros-noetic-tf ros-noetic-gazebo-ros-pkgs -y
```

Then rebuild:

```bash
cd ~/ASTRO_GazeboVisualizer
rm -rf catkin_ws/build catkin_ws/devel catkin_ws/install
bash build_gazebo_visualizer.sh
```

---

### Problem: MATLAB cannot connect to ROS

In WSL, get IP:

```bash
hostname -I
```

In MATLAB:

```matlab
rosshutdown
rosinit('http://WSL_IP:11311')
```

Example:

```matlab
rosinit('http://172.28.112.45:11311')
```

Also check that Gazebo/ROS launch is still running in WSL.

---

### Problem: Gazebo opens but spacecraft do not move

Check topics in WSL:

```bash
rostopic list
rostopic echo /astro/chaser/state
```

If no messages appear, MATLAB is not publishing.

In MATLAB, run:

```matlab
rostopic list
pubs = run_gazebo_visualizer();
publish_gazebo_demo_orbit
```

---

### Problem: Lighting command does nothing

Make sure Gazebo launch is running and the lighting node exists:

```bash
rostopic list | grep lighting
```

Expected topics may include:

```text
/astro/visualizer/lighting_mode
/astro/visualizer/sun_direction
```

Then in MATLAB:

```matlab
set_gazebo_lighting('bright')
set_gazebo_lighting('eclipse')
```

---

## 16. Quick command reference

### Build visualizer

```bash
rm -rf ~/ASTRO_GazeboVisualizer
cp -r /mnt/g/Github/ASTRO/GazeboVisualizer ~/ASTRO_GazeboVisualizer
cd ~/ASTRO_GazeboVisualizer
source /opt/ros/noetic/setup.bash
bash build_gazebo_visualizer.sh
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
```

### Launch visualizer

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

### MATLAB run

```matlab
cd('G:\Github\ASTRO\Matlab')
initialization
```

### MATLAB demo

```matlab
pubs = run_gazebo_visualizer();
publish_gazebo_demo_orbit
```

### MATLAB lighting

```matlab
set_gazebo_lighting('day')
set_gazebo_lighting('eclipse')
set_gazebo_lighting([1;0;-0.2])
```

---

## 17. Notes on scale and visualization

Real inertial orbit positions are very large. The visualizer may apply internal centering and scaling so Gazebo remains usable.

This does not change the real MATLAB state. It only affects visualization.

Recommended behavior:

```text
MATLAB state    = true inertial position/velocity/attitude
Gazebo display  = scaled and centered visualization
```

This is normal for orbital visualization.

---

## 18. Recommended workflow

For development:

```text
1. Start Gazebo once.
2. Run MATLAB demo publisher.
3. Confirm movement.
4. Run ASTRO simulation.
5. Adjust lighting/view as needed.
```

For debugging:

```bash
rostopic list
rostopic echo /astro/chaser/state
rostopic echo /astro/target/state
```

For visual presentation:

```matlab
set_gazebo_lighting('bright')
```

For eclipse/night-side testing:

```matlab
set_gazebo_lighting('eclipse')
```
