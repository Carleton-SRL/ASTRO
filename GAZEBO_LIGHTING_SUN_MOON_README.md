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
