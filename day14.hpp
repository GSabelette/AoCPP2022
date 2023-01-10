#include "common/common.hpp"

#define MAX_DEPTH 170

using point = std::pair<int, int>;
using segment = std::pair<point, point>;

static point sandfall(500, 0);

struct day14 {
    std::unordered_set<point, hashes::PairHash<int,int>> filled;

    day14();

    template <typename F>
    bool spawn_sand(std::unordered_set<point, hashes::PairHash<int,int>>& filled, F end_condition);

    uint64_t part_one();
    uint64_t part_two();
};