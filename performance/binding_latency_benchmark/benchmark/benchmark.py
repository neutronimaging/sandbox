#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import gc
import importlib
import sys
import time
from pathlib import Path
from typing import Callable

def py_add(a: float, b: float) -> float:
    """Pure Python baseline add function."""
    return a + b

def time_calls(func: Callable[[float, float], float], n_calls: int, repeats: int) -> float:
    """Return best execution time in seconds for n_calls function calls."""
    best = float("inf")
    for _ in range(repeats):
        gc.disable()
        t0 = time.perf_counter()
        acc = 0.0
        for i in range(n_calls):
            acc += func(float(i), 1.0)
        elapsed = time.perf_counter() - t0
        gc.enable()

        # Prevent the loop from becoming semantically irrelevant.
        if acc <= 0.0:
            raise RuntimeError("unexpected benchmark accumulator value")
        best = min(best, elapsed)
    return best


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--build-dir",
        type=Path,
        default=Path("build"),
        help="Directory containing the compiled extension modules",
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=Path("binding_latency_results.csv"),
        help="Output CSV file",
    )
    parser.add_argument(
        "--repeats",
        type=int,
        default=7,
        help="Repeat each timing and store the best result",
    )
    parser.add_argument(
        "--loops",
        type=int,
        nargs="*",
        # default=[10, 30, 100, 300, 1_000, 3_000, 10_000, 30_000, 100_000, 300_000, 1_000_000, 3_000_000, 10_000_000 , 30_000_000, 100_000_000, 300_000_000, 1_000_000_000, 3_000_000_000, 10_000_000_000],
        default=[10, 30, 100, 300, 1_000, 3_000, 10_000, 30_000, 100_000, 300_000],
        help="Exactly ten loop lengths by default",
    )
    args = parser.parse_args()

    build_dir = args.build_dir.resolve()
    sys.path.insert(0, str(build_dir))

    modules = {
        "python": type('Module', (), {'add': staticmethod(py_add)})(),
        "pybind11": importlib.import_module("pybind_add"),
        "nanobind": importlib.import_module("nanobind_add"),
    }

    rows: list[dict[str, str | int | float]] = []
    for n_calls in args.loops:
        for binding_name, module in modules.items():
            elapsed = time_calls(module.add, n_calls, args.repeats)
            rows.append(
                {
                    "binding": binding_name,
                    "number of calls": n_calls,
                    "execution time": elapsed,
                }
            )
            print(f"{binding_name:8s} {n_calls:9d} calls: {elapsed:.6e} s")

    with args.output.open("w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["binding", "number of calls", "execution time"],
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"\nWrote {args.output}")


if __name__ == "__main__":
    main()
