#include "common/common.hpp"

using packetPair = std::pair<std::string, std::string>;

struct day13 {
    std::vector<packetPair> packetPairs;

    day13();

    int part_one();
    int part_two();
};