#include "common/common.hpp"

using screen = std::array<std::string, 6>;

struct day10 {
    std::vector<std::string> instructions;  

    day10();

    int part_one();
    screen part_two();
};