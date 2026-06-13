# ASTRO Gazebo visualizer auto ROS initialization

This build lets MATLAB initialize the ROS connection automatically for the Gazebo visualizer.

## Normal workflow

1. Start WSL Ubuntu.
2. Launch the Gazebo visualizer:

```bash
source /opt/ros/noetic/setup.bash
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

3. Open MATLAB on Windows.
4. Run only the main ASTRO script:

```matlab
cd('G:\Github\ASTRO\Matlab')
initialization
```

MATLAB will call `run_gazebo_visualizer` automatically, detect the WSL IP using:

```text
wsl hostname -I
```

and run:

```matlab
rosinit('http://<WSL_IP>:11311')
```

## Topics published by MATLAB

```text
/astro/target/state   nav_msgs/Odometry
/astro/chaser/state   nav_msgs/Odometry
```

Each topic contains inertial state:

```text
[pos; vel; quat; omega]
```

ASTRO quaternion order is scalar-last:

```text
[qx; qy; qz; qw]
```

so this build sets:

```matlab
SimulationOptions.gazebo_quaternion_order = 'xyzw';
```

## Manual override

If auto-detection fails, edit `initialization.m`:

```matlab
SimulationOptions.gazebo_master_uri = 'http://<WSL_IP>:11311';
```

For example:

```matlab
SimulationOptions.gazebo_master_uri = 'http://172.28.219.151:11311';
```
