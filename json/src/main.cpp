#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    json j = {
        {"project", "json-demo"},
        {"answer",  42},
        {"values",  {1,2,3}},
        {"pi",      3.14159}
    };

    std::cout << j.dump(2) << "\n";
    std::cout << "answer = " << j.at("answer").get<int>() << "\n";
    return 0;
}

