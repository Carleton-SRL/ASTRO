# ASTRO ROS1/Gazebo Standalone Orbit Visualizer

This is a clean ROS1/Gazebo visualizer for MATLAB-published spacecraft inertial states.
It is Astrobee-style in the sense that Gazebo runs as a standalone visualization process and ROS topics drive the visual state.

## State topics

MATLAB publishes `nav_msgs/Odometry`:

- `/astro/target/state`
- `/astro/chaser/state`

Each message represents:

```text
[pos; vel; quat; omega]
```

where:

- `pos` = inertial position, 3x1
- `vel` = inertial velocity, 3x1
- `quat` = attitude quaternion, 4x1
- `omega` = angular velocity, 3x1

The MATLAB helper assumes quaternion order `wxyz` by default.

## Important visualization scaling

Gazebo cannot conveniently display true ECI magnitudes at kilometer/orbital scale. The ROS bridge keeps the true state in the ROS messages, then applies visualization-only scaling.

Default launch settings:

```bash
position_units:=km
visual_scale:=0.01
center_mode:=target
```

This means:

- MATLAB positions are interpreted as kilometers.
- They are converted to meters internally.
- Then multiplied by `0.01` for Gazebo display.
- The target is centered at Gazebo world origin.

The chaser therefore appears at its relative orbit location around the target.

## WSL build

Copy the visualizer into the Linux filesystem before building:

```bash
rm -rf ~/ASTRO_GazeboVisualizer
cp -r /mnt/g/Github/ASTRO/GazeboVisualizer ~/ASTRO_GazeboVisualizer
cd ~/ASTRO_GazeboVisualizer
bash build_gazebo_visualizer.sh
```

## Run Gazebo

```bash
cd ~/ASTRO_GazeboVisualizer
bash run_gazebo_visualizer.sh
```

Optional scale changes:

```bash
bash run_gazebo_visualizer.sh visual_scale:=0.1
bash run_gazebo_visualizer.sh center_mode:=inertial visual_scale:=0.00001
```

## MATLAB connection

Find WSL IP:

```bash
hostname -I
```

In MATLAB on Windows:

```matlab
rosshutdown
rosinit('http://<WSL_IP>:11311')
cd('G:\Github\ASTRO\Matlab')
pubs = run_gazebo_visualizer();
publish_gazebo_demo_orbit
```

## Publishing from your actual ASTRO simulation

Inside the simulation loop, call:

```matlab
GazeboViz.publishInertialState(pubs.target, targetState, 'eci', 'target', 'wxyz');
GazeboViz.publishInertialState(pubs.chaser, chaserState, 'eci', 'chaser', 'wxyz');
```

where:

```matlab
targetState = [r_target; v_target; q_target; omega_target];
chaserState = [r_chaser; v_chaser; q_chaser; omega_chaser];
```

Use `'xyzw'` instead of `'wxyz'` if your quaternion is scalar-last.
# ASTRO Gazebo Sun/Moon + Runtime Lighting

This package extends the ROS1/Gazebo ASTRO visualizer with:

- Sun visual model: `sun_visual`
- Moon visual model: `moon`
- Runtime lighting controller node: `lighting_control.py`
- MATLAB runtime lighting command: `set_gazebo_lighting.m`
- Optional Sun/Moon state topics:
  - `/astro/sun/state`
  - `/astro/moon/state`

## Launch Gazebo in WSL

```bash
rm -rf ~/ASTRO_GazeboVisualizer
cp -r /mnt/g/Github/ASTRO/GazeboVisualizer ~/ASTRO_GazeboVisualizer
cd ~/ASTRO_GazeboVisualizer
source /opt/ros/noetic/setup.bash
bash build_gazebo_visualizer.sh
source ~/ASTRO_GazeboVisualizer/catkin_ws/devel/setup.bash
roslaunch ~/ASTRO_GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/launch/orbit_visualizer.launch
```

## Run MATLAB

```matlab
cd('G:\Github\ASTRO\Matlab')
initialization
```

The MATLAB visualizer setup now creates publishers for:

```text
/astro/target/state        nav_msgs/Odometry
/astro/chaser/state        nav_msgs/Odometry
/astro/sun/state           nav_msgs/Odometry
/astro/moon/state          nav_msgs/Odometry
/astro/viz/lighting_mode   std_msgs/String
/astro/viz/sun_direction   geometry_msgs/Vector3
```

## Change lighting in real time from MATLAB

```matlab
set_gazebo_lighting('day')
set_gazebo_lighting('dawn')
set_gazebo_lighting('eclipse')
set_gazebo_lighting('moonlight')
set_gazebo_lighting('soft')
set_gazebo_lighting('bright')
```

Custom light-ray direction:

```matlab
set_gazebo_lighting([1; 0; -0.2])
```

## Publish Sun and Moon states

```matlab
pubs = run_gazebo_visualizer();
publish_gazebo_celestial_state(pubs)
```

Or pass actual inertial Sun/Moon states using the same ASTRO state format:

```text
[pos; vel; quat; omega]
```

The quaternion convention is scalar-last:

```text
[qx; qy; qz; qw]
```

## Notes

The spacecraft use the normal visualization scale. Celestial bodies use a separate scale to keep Sun/Moon visible in the Gazebo scene:

```xml
<arg name="celestial_visual_scale" default="0.000001" />
```

You can change this in `orbit_visualizer.launch`.
