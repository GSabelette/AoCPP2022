#include "common/common.hpp"

using point = std::pair<int,int>;

struct day15 {
    std::unordered_map<point, point, hashes::PairHash<int,int>> sensor_map;

    day15();

    uint64_t part_one();
};