#pragma once

inline double add(double a, double b) noexcept {
    return a + b;
}

inline double add_loop(int n, double a, double b) noexcept
{
    double res=0.0;
    
    for (size_t i=0UL; i<n; ++i)
    {
        res += add(float(i), 1.0);
    }
    return res;
}