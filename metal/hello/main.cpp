#include <Metal/Metal.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>  

// Current problem: the buffers are not allocated correctly, the data is not copied to the buffers correctly, and the kernel is not executed correctly.

int add_vectors(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& c) {
    for (size_t i = 0; i < a.size(); ++i) {
        c[i] = a[i] + b[i];
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // Create some data
    std::clog<< "Creating data" <<std::endl;
    size_t N = 1UL<<28;
    std::vector<float> a(N, 1.0f);
    std::vector<float> b(N, 2.0f);
    std::vector<float> c(N, 0.0f);

    auto start = std::chrono::high_resolution_clock::now();
    if (argc == 1)
    {
        std::clog<< "Start GPU processing" <<std::endl;
        // Get the default device
        id<MTLDevice> device = MTLCreateSystemDefaultDevice();

        if (device==nil) {
            std::clog<< "Failed to create a Metal device" <<std::endl;
            return -1;
        }
        std::clog<< "device: " << device <<std::endl;
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



        // Create buffers
        id<MTLBuffer> bufferA = [device newBufferWithBytes:a.data() length:a.size()*sizeof(float) options:MTLResourceStorageModeShared];
        id<MTLBuffer> bufferB = [device newBufferWithBytes:b.data() length:b.size()*sizeof(float) options:MTLResourceStorageModeShared];
        id<MTLBuffer> bufferC = [device newBufferWithBytes:c.data() length:c.size()*sizeof(float) options:MTLResourceStorageModeShared];

        // std::clog<< "*a: " << a.data()<<", size:"<<a.size() <<std::endl;
        // std::clog<< "*b: " << b.data()<<", size:"<<b.size() <<std::endl;
        // std::clog<< "*c: " << c.data()<<", size:"<<c.size() <<std::endl;
        // std::clog<< "*bufferA: " << [bufferA contents] <<std::endl;
        // std::clog<< "*bufferB: " << [bufferB contents] <<std::endl;
        // std::clog<< "*bufferC: " << [bufferC contents] <<std::endl;
        // Create a command buffer
        // std::clog<< "Creating command buffer" <<std::endl;
        id<MTLCommandBuffer> commandBuffer = [queue commandBuffer];

        // Create a compute command encoder
        // std::clog<< "Creating command encoder" <<std::endl;
        id<MTLComputeCommandEncoder> encoder = [commandBuffer computeCommandEncoder];

        // Set the compute pipeline state
        // std::clog<< "Creating pipeline state" <<std::endl;
        id<MTLComputePipelineState> pipelineState = [device newComputePipelineStateWithFunction:function error:&error];
        [encoder setComputePipelineState:pipelineState];


        // Set the buffers
        // std::clog<< "Set buffers" <<std::endl;
        [encoder setBuffer:bufferA offset:0 atIndex:0];
        [encoder setBuffer:bufferB offset:0 atIndex:1];
        [encoder setBuffer:bufferC offset:0 atIndex:2];

        // Dispatch the compute command
        MTLSize gridSize  = MTLSizeMake(a.size(), 1, 1);
        MTLSize groupSize = MTLSizeMake(1024, 1, 1);
        // std::clog<< "Dispatching thread groups" <<std::endl;
        [encoder dispatchThreadgroups:gridSize threadsPerThreadgroup:groupSize];

        // End encoding
        [encoder endEncoding];

        // Commit the command buffer
        // std::clog<< "Commit command buffer" <<std::endl;
        [commandBuffer commit];

        // Wait for the command buffer to complete
        [commandBuffer waitUntilCompleted];

        // std::clog<< "Command buffer completed" <<std::endl;

        std::copy_n(static_cast<float*>([bufferC contents]), N, c.begin());
    }
    else
    {
        std::clog<< "Start CPU processing" <<std::endl;
        add_vectors(a, b, c);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end-start;
    std::clog<< "Done (time:"<<elapsed.count()<<")" <<std::endl;
    for (size_t i = 0; i<10; ++i)
    {
        std::clog << a[i]<<"+"<<b[i]<<"="<<c[i] << std::endl;
    }

    return 0;
}