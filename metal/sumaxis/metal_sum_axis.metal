#include <metal_stdlib>
using namespace metal;

kernel void sum_axis_y(
    texture2d<float, access::read> inTexture [[texture(0)]],
    device float* outSums [[buffer(0)]],
    uint2 gid [[thread_position_in_grid]]
) {
    if (gid.x >= inTexture.get_width()) return;
    if (gid.y != 0) return; // Only do the work in the first row

    float sum = 0.0;
    for (uint y = 0; y < inTexture.get_height(); ++y) {
        sum += inTexture.read(uint2(gid.x, y)).r;
    }
    outSums[gid.x] = sum;
}
