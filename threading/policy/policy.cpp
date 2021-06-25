#include <algorithm>
#include <cmath>
#include <vector>
#include <execution>

int main(int argc, char * argv[])
{
	size_t N = 10000UL;
	std::vector<double> vec(1000,N);
	std::vector<double> out(0,N);


	std::transform(std::execution::par, vec.begin(), vec.end(), out.begin(),
            [](double v) {
                return std::sqrt(std::sin(v)*std::cos(v));
            }
);

}
