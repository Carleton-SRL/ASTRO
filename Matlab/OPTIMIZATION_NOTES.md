# MATLAB Performance Patch Notes

This patched version keeps the original project layout but adds runtime switches and faster propagation helpers.

## Main changes

1. Added fixed-step RK4 propagation helpers:
   - `+dynamics/RK4_step.m`
   - `+dynamics/propagate_fixed_step.m`

2. Updated `RunSimulation.m`:
   - Uses fixed-step RK4 by default instead of repeatedly starting `ode45` inside the main loop.
   - Keeps the original `ode45` path behind `SimulationOptions.use_fixed_step_propagator = false`.
   - Replaces the CPU-burning busy-wait loop with `pause(remainingTime)`.
   - Adds ROS publish throttling options.
   - Normalizes propagated quaternions after attitude propagation.
   - Tracks propagation timing in `SimulationTiming.propagation_sec`.

3. Updated `initialization.m`:
   - Adds fidelity modes: `fast`, `medium`, `high`.
   - Adds runtime switches for fixed-step propagation, ROS publishing, post-processing, and real-time pacing.
   - Wraps post-processing in `SimulationOptions.enable_postprocessing`.

4. Updated `+dynamics/GravityFieldPerturbiation.m`:
   - Precomputes `cos(m*lon)`, `sin(m*lon)`, and gravity-field powers.
   - Uses `m = 0:min(n,nmin)` to avoid invalid/unneeded harmonic terms.

5. Updated `+dynamics/simulator.m`:
   - Moves gravitational constants into persistent variables so they are not recreated every dynamics call.

## Recommended performance modes

### Fast debugging/controller mode

In `initialization.m`:

```matlab
SimulationOptions.fidelity_mode = 'fast';
SimulationOptions.enable_postprocessing = false;
SimulationOptions.realtime_mode = false;
SimulationOptions.ros_publish_skip = 5;
```

### Medium-fidelity mode

```matlab
SimulationOptions.fidelity_mode = 'medium';
SimulationOptions.use_fixed_step_propagator = true;
```

### Original dynamics validation mode

```matlab
SimulationOptions.fidelity_mode = 'high';
SimulationOptions.use_fixed_step_propagator = false;
```

Use this to compare the new RK4 path against the original `ode45` behavior.

## Validation recommendation

Run once with:

```matlab
SimulationOptions.use_fixed_step_propagator = false;
```

Then run again with:

```matlab
SimulationOptions.use_fixed_step_propagator = true;
```

Compare final target/chaser states, relative position error, and attitude error. If the RK4 error is too large, reduce `dt_GPS` in `initialize_time.m` or use the original `ode45` path for high-accuracy reference runs.
