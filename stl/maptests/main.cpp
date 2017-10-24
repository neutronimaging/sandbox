#include <iostream>
#include <map>

int main(int argc, char *argv[])
{

    std::map<int,std::pair<float,int> > a;

    a[0].first=1.0f;
    a[0].second=1;

    a[1].first+=10.0f;
    a[1].second++;

    for (auto it=a.begin(); it!=a.end(); ++it) {
        std::pair<float,int> & item= (*it).second;
        std::cout<< item.first << ", " << item.second <<std::endl;
    }

    return 0;
}
