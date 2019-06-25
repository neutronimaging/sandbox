#include "processor.h"

int main(int argc, char *argv[])
{
    Processor p;

    const size_t N=1024UL;
//    p.tester(N*N*N);


    p.ftester(N*N*N);
    return 0;
}
