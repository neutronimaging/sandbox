#include <metal_stdlib>
using namespace metal;

kernel void add_vectors(device float4 *a [[ buffer(0) ]], 
                        device float4 *b [[ buffer(1) ]], 
                        device float4 *c [[ buffer(2) ]], 
                        uint id [[ thread_position_in_grid ]]) {
    c[id] = a[id] + b[id];
}
