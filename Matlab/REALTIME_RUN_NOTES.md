# Real-time/HIL run notes

This patch makes the MATLAB loop wall-clock paced and deterministic enough for real-time hardware-in-the-loop testing.

## Recommended real-time defaults

In `initialization.m`:

```matlab
SimulationOptions.fidelity_mode = 'medium';
SimulationOptions.use_fixed_step_propagator = true;
SimulationOptions.realtime_mode = true;
SimulationOptions.realtime_time_scale = 1.0;
SimulationOptions.ros_publish_skip = 2;
SimulationOptions.low_rate_ros_publish_skip = 5;
SimulationOptions.publish_clock_every_step = true;
SimulationOptions.enable_postprocessing = false;
SimulationOptions.verbose_timing = true;
```

Use `fidelity_mode = 'high'` only for offline validation unless your machine can complete every step faster than the simulation step size.

## What changed for real-time

- The old CPU-burning busy-wait loop was replaced with `pause(remainingTime)`.
- The main loop now tracks per-step runtime, slack, overrun count, and max overrun.
- `/clock` and `Simulation_Clock_ROS` can publish every step, while heavier telemetry is throttled.
- Adaptive `ode45` is disabled by default in favor of the fixed-step RK4 propagator.
- Post-processing is disabled by default so plotting cannot block real-time execution.

## How to check if it is truly real-time

Run with:

```matlab
SimulationOptions.verbose_timing = true;
initialization
```

At the end, check:

```matlab
SimulationTiming.overrun_count
SimulationTiming.max_overrun_sec
mean(SimulationTiming.step_sec(SimulationTiming.step_sec>0))
```

For a real-time run, `mean(step_sec)` must be below `dt`, and `overrun_count` should be zero or very small.

## If overruns occur

Use this order:

1. Set `SimulationOptions.fidelity_mode = 'fast'`.
2. Increase `SimulationOptions.ros_publish_skip` to 5 or 10.
3. Increase `SimulationOptions.low_rate_ros_publish_skip` to 10 or 20.
4. Keep `SimulationOptions.enable_postprocessing = false`.
5. Keep `SimulationOptions.use_fixed_step_propagator = true`.
6. Reduce GPS simulator update rate only if the hardware allows it.

## Important

Real-time means the loop keeps pace with wall clock. It does not guarantee hard real-time scheduling because MATLAB and desktop OS scheduling are not hard real-time. For strict hard real-time, deploy the fixed-step GNC core to Simulink Real-Time, Speedgoat, a real-time Linux target, or generated C/C++ code.


## Optional terminal simulation clock

The real-time package now includes an efficient single-line terminal clock controlled from `initialization.m`:

```matlab
SimulationOptions.show_simulation_clock = true;
SimulationOptions.clock_display_period = 1.0;
SimulationOptions.clock_display_wall_ratio = true;
```

This is intentionally not printed every integration step. It updates in-place once per simulated second by default, so it has negligible impact on real-time/HIL execution. Set `clock_display_wall_ratio = false` to show only `HH:MM:SS`, or set `show_simulation_clock = false` to disable command-window updates entirely.
