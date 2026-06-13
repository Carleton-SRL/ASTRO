#!/usr/bin/env bash
set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source /opt/ros/noetic/setup.bash
source "$SCRIPT_DIR/catkin_ws/devel/setup.bash"
roslaunch astro_orbit_gazebo orbit_visualizer.launch "$@"
