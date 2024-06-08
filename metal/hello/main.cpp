#include <Metal/Metal.h>
#include <vector>
#include <iostream>
#include <fstream>

int main() {
    // Get the default device
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();

    // Load the shader from the file
    NSError* error = nil;
    NSString* shaderPath = [[NSBundle mainBundle] pathForResource:@"shader" ofType:@"metallib"];
    if (shaderPath == nil) {
        NSLog(@"Failed to find shader.metallib");
        return -1;
    }
    NSURL* shaderURL = [NSURL fileURLWithPath:shaderPath];
    id<MTLLibrary> library = [device newLibraryWithURL:shaderURL error:&error];

    // Get the kernel function
    id<MTLFunction> function = [library newFunctionWithName:@"add_vectors"];

    // Create a command queue
    id<MTLCommandQueue> queue = [device newCommandQueue];

    // Create some data
    size_t N = 1024;
    std::vector<float> a(N, 1.0f);
    std::vector<float> b(N, 2.0f);
    std::vector<float> c(N, 0.0f);

    // Create buffers
    id<MTLBuffer> bufferA = [device newBufferWithBytes:a.data() length:a.size()*sizeof(float) options:MTLResourceStorageModeShared];
    id<MTLBuffer> bufferB = [device newBufferWithBytes:b.data() length:b.size()*sizeof(float) options:MTLResourceStorageModeShared];
    id<MTLBuffer> bufferC = [device newBufferWithBytes:c.data() length:c.size()*sizeof(float) options:MTLResourceStorageModeShared];

    // Create a command buffer
    id<MTLCommandBuffer> commandBuffer = [queue commandBuffer];

    // Create a compute command encoder
    id<MTLComputeCommandEncoder> encoder = [commandBuffer computeCommandEncoder];

    // Set the compute pipeline state
    id<MTLComputePipelineState> pipelineState = [device newComputePipelineStateWithFunction:function error:&error];
    [encoder setComputePipelineState:pipelineState];


    // Set the buffers
    [encoder setBuffer:bufferA offset:0 atIndex:0];
    [encoder setBuffer:bufferB offset:0 atIndex:1];
    [encoder setBuffer:bufferC offset:0 atIndex:2];

    // Dispatch the compute command
    MTLSize gridSize  = MTLSizeMake(a.size(), 1, 1);
    MTLSize groupSize = MTLSizeMake(64, 1, 1);
    [encoder dispatchThreadgroups:gridSize threadsPerThreadgroup:groupSize];

    // End encoding
    [encoder endEncoding];

    // Commit the command buffer
    [commandBuffer commit];

    // Wait for the command buffer to complete
    [commandBuffer waitUntilCompleted];
    
    memcpy(c.data(), [bufferC contents], N*sizeof(float));
    // The result is now in the 'c' buffer
    // ...
    std::ofstream logFile("log.txt");
    auto* oldClogBuffer = std::clog.rdbuf(); // Save old buf
    std::clog.rdbuf(logFile.rdbuf()); // Redirect std::clog to log.txt

    for (size_t i = 0; i<10; ++i)
    {
        std::clog << c[i] << std::endl;
    }

    return 0;
}