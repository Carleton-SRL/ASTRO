# ASTRO High-Fidelity Gazebo Visualizer Notes

This package extends the working ROS1/Gazebo visualizer with:

- Procedural textured Earth with clouds and atmosphere visual shells.
- Textured Moon model.
- Emissive Sun model.
- MATLAB-published `/astro/sun/state` and `/astro/moon/state` topics.
- Dynamic Gazebo directional light control driven by MATLAB Sun state.
- Runtime lighting mode and intensity control.
- CAD-ready spacecraft model folders.

## MATLAB topics

All states use `nav_msgs/Odometry`:

```text
/astro/target/state
/astro/chaser/state
/astro/sun/state
/astro/moon/state
```

MATLAB state vector:

```text
[pos; vel; quat; omega]
```

with scalar-last quaternion `[qx; qy; qz; qw]`.

## Lighting

```matlab
set_gazebo_lighting('day')
set_gazebo_lighting('dawn')
set_gazebo_lighting('eclipse')
set_gazebo_lighting('moonlight')
set_gazebo_lighting('bright', 1.4)
set_gazebo_lighting([1; 0; -0.2])
```

## CAD replacement

Place `.dae` visual meshes and simplified collision meshes in:

```text
GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/models/chaser/meshes/
GazeboVisualizer/catkin_ws/src/astro_orbit_gazebo/models/target/meshes/
```
