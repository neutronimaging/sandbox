#include <Metal/Metal.hpp>
#include <vector>
#include <iostream>
#include <cassert>

int main() {
    using namespace MTL;

    // --- Setup device and command queue
    auto device = CreateSystemDefaultDevice();
    auto commandQueue = device->newCommandQueue();

    // --- Load Metal library
    NSError* err = nullptr;
    NSString* srcPath = @"metal_sum_axis.metallib";
    auto nsLibData = NSData::dataWithContentsOfFile(srcPath);
    auto lib = device->newLibraryWithData(nsLibData, &err);
    assert(lib && "Failed to load Metal library");

    auto func = lib->newFunctionWithName(@"sum_axis_y");
    auto pipeline = device->newComputePipelineStateWithFunction(func, &err);

    // --- Image (example: 64x32 float values)
    constexpr size_t width = 64, height = 32;
    std::vector<float> imageData(width * height, 1.0f); // uniform values for simplicity

    // --- Texture descriptor
    MTL::TextureDescriptor* desc = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormatR32Float, width, height, false);
    desc->setUsage(MTL::TextureUsageShaderRead);
    auto texture = device->newTexture(desc);

    // --- Copy image data to texture
    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    texture->replaceRegion(region, 0, imageData.data(), width * sizeof(float));

    // --- Output buffer
    auto buffer = device->newBuffer(width * sizeof(float), MTL::ResourceStorageModeShared);

    // --- Command buffer and encoder
    auto commandBuffer = commandQueue->commandBuffer();
    auto encoder = commandBuffer->computeCommandEncoder();

    encoder->setComputePipelineState(pipeline);
    encoder->setTexture(texture, 0);
    encoder->setBuffer(buffer, 0, 0);

    MTL::Size gridSize(width, 1, 1);
    MTL::Size threadgroupSize(16, 1, 1); // Tune for your GPU
    encoder->dispatchThreads(gridSize, threadgroupSize);
    encoder->endEncoding();

    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();

    // --- Read result
    auto* results = static_cast<float*>(buffer->contents());
    for (size_t x = 0; x < width; ++x)
        std::cout << "Sum at x=" << x << ": " << results[x] << '\n';

    return 0;
}
