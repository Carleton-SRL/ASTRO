# Fast Offline Simulation Mode

This patch adds an explicit fast offline mode for running the MATLAB simulation as fast as possible when real-time HIL behavior is not needed.

## Main switch

In `initialization.m`:

```matlab
SimulationOptions.execution_mode = 'fast_offline';
```

This automatically sets:

```matlab
SimulationOptions.fidelity_mode = 'fast';
SimulationOptions.use_fixed_step_propagator = true;
SimulationOptions.gps_compatible_propagation = false;
SimulationOptions.max_propagation_step = inf;
SimulationOptions.realtime_mode = false;
SimulationOptions.publish_ros = false;
SimulationOptions.publish_clock_every_step = false;
SimulationOptions.show_simulation_clock = false;
SimulationOptions.enable_postprocessing = false;
```

and:

```matlab
hardware_flags = [false; false; false];
centralbody = [0;0;0;0;0;0;0;0;0;0];
```

## Important change

The previous RK4 implementation still used the GPS-compatible propagation grid:

```matlab
tpropGPS = 0:0.02:1;
```

That means every one-second simulation step was still internally propagated over about 50 RK4 substeps. Since each RK4 step calls the dynamics function 4 times, this caused roughly 200 dynamics evaluations per spacecraft per simulation second.

With `fast_offline`, when the GPS simulator is off, the code now uses:

```matlab
tpropStep = [0 dt_data];
```

This gives one RK4 step per main propagation interval instead of the 0.02 s GPS grid.

## Realtime/HIL mode

For HIL testing, use:

```matlab
SimulationOptions.execution_mode = 'realtime_hil';
```

This preserves wall-clock pacing, terminal clock display, ROS publication, and GPS-compatible propagation.

## Custom accuracy/speed compromise

For a middle ground, use `custom` and set:

```matlab
SimulationOptions.execution_mode = 'custom';
SimulationOptions.max_propagation_step = 0.1;   % 10 RK4 substeps per second
SimulationOptions.gps_compatible_propagation = false;
SimulationOptions.realtime_mode = false;
SimulationOptions.publish_ros = false;
```

Smaller `max_propagation_step` is more accurate but slower.
