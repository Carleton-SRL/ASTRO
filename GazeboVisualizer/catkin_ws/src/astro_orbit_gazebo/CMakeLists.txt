cmake_minimum_required(VERSION 3.0.2)
project(astro_orbit_gazebo)
find_package(catkin REQUIRED COMPONENTS
  rospy
  nav_msgs
  geometry_msgs
  std_msgs
  visualization_msgs
  gazebo_msgs
  tf
)
catkin_package()
catkin_install_python(PROGRAMS
  scripts/state_to_gazebo.py
  scripts/orbit_marker_engine.py
  scripts/lighting_control.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch worlds models rviz config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
