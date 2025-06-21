# 🛰️ Welcome to ASTRO - Advanced Simulation Testbed for Robotics on Orbit

This repository hosts the software for the **Advanced Simulation Testbed for Robotics on Orbit**, developed to support experimental validation of spacecraft guidance, navigation, and control (GNC) algorithms for autonomous proximity operations, rendezvous, formation flying, and cooperative maneuvers in space-like environments. The testbed is primarily aimed at enabling realistic real-time testing of space flight scenarios, including perturbation modeling, sensor emulation, and communication constraints.

---

## 💡 Features

- 🌌 Perturbation modeling for orbital dynamics  
- 📡 Emulated onboard sensors (e.g., GPS, RADAR) with configurable noise and update rates  
- 🔁 Modeling of inter-satellite communication links  
- 🛰️ Support for relative navigation strategies including angle-only tracking and nonlinear observers  
- 🎯 Capability to simulate both cooperative and adversarial scenarios (e.g., pursuit-evasion)

---

## 📂 Repository Contents

This repository includes:

- `MATLAB/Simulink` models for spacecraft dynamics, GNC, and sensor emulation  
- `ROS`-based infrastructure with real-time integration and code generation for NVIDIA Jetson hardware  
- `C++` ROS nodes and drivers for hardware interfacing  
- Configuration files and mission templates for replicable experiments

---

## 📚 Documentation

The repository is actively maintained and intended to serve both as a research platform and an educational tool. For a detailed description of the testbed architecture, software stack, and experiment implementation, please refer to **Chapter 8** of the PhD thesis:

> _"Autonomous GNC of Spacecraft Rendezvous and Formation Flying on Perturbed Highly Elliptical Orbits"_  
> by **Yazan Chihabi**

---

## 🛠️ Contributing

Contributions, bug reports, and feature requests are welcome to help improve the platform.

---

