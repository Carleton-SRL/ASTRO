# Welcome to Space Flight Mechanics Testbed
This testbed has been developed to support experimental validation of spacecraft guidance, navigation, and control (GNC) algorithms for autonomous proximity operations, rendezvous, formation flying, and cooperative maneuvers in space-like environments. The testbed is primarily aimed at enabling realistic real-time testing of space flight scenarios, including perturbation modeling, sensor emulation, and communication constraints.

The testbed includes emulated onboard sensors such as GPS and RADAR to simulate realistic sensor behavior under varied noise and update rate conditions. It also supports the modeling of inter-satellite links and relative navigation techniques, including angle-only tracking and nonlinear observer methods. The modularity of the system allows the testing of both cooperative and adversarial interaction scenarios (e.g., pursuit-evasion dynamics).

This repository contains the full software stack for the testbed, including:

  (1) MATLAB/Simulink models for the spacecraft dynamics, control systems, and sensor emulation.

  (2) Real-time ROS integration and auto-code generation pipelines targeting NVIDIA Jetson hardware.

  (3) C++ drivers and ROS nodes for real hardware interfacing.

  (4) Configuration files and mission templates for experiment setup and replication.

The repository is actively maintained and intended to serve both as a research platform and an educational tool. For a complete description of the testbed architecture, experimental setup, and implementation details, please refer to Chapter 8 of the PhD thesis titled "Autonomous GNC of Spacecraft Rendezvous and Formation Flying on Perturbed Highly Elliptical Orbits." Contributions, bug reports, and feature requests are welcome to help improve the platform.
