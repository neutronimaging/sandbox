#include <iostream>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "QuartzCore/QuartzCore.hpp"

#include "MetalAdder.hpp"

int main(int argc, char *argv[])
{
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    if (device == nullptr){
        std::clog<<"Failed to create device."<<std::endl;
        return 1;
    }

    std::clog<<"Device created: "<<device<<std::endl; 
    // MetalAdder *adder = new MetalAdder(device);

    // adder->sendComputeCommand(); 
    // adder->verifyResults();
}