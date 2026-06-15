# pybind11 vs nanobind call-latency benchmark

This project builds two Python extension modules exposing the same C++ function:

```cpp
inline double add(double a, double b) noexcept { return a + b; }
```

The Python benchmark calls both bindings for ten loop lengths and writes a CSV file with:

- `binding`
- `number of calls`
- `execution time`

## Setup


```bash
pixi install
```

## Build

```bash
pixi run configure
pixi run build
```

## Run benchmark

```bash
python benchmark/benchmark.py --build-dir build --output binding_latency_results.csv
```

The script uses the best of several repeats for each loop length. This reduces, but does not remove, noise from the OS scheduler and CPU frequency scaling.
