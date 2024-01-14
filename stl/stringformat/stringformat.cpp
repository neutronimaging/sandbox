#include <cassert>
#include <format>
#include <string>
#define FMT_HEADER_ONLY

int main()
{
    std::string message = std::vformat("The answer is {}.", 42);
    assert(message == "The answer is 42.");
}