#!/usr/bin/env bash
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source /opt/ros/noetic/setup.bash
cd "$SCRIPT_DIR/catkin_ws"
catkin_make
printf '\nBuild complete. Run:\n  source %s/catkin_ws/devel/setup.bash\n  roslaunch astro_orbit_gazebo orbit_visualizer.launch\n' "$SCRIPT_DIR"
