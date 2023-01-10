#include "day14.hpp"

day14::day14() {
    auto input = profile("Opening file", readFile, "inputs/day14.input");
    auto parse_point = [](const std::string& s) {
        auto split = split_string(s, ",");
        return point(std::stoi(split[0]), std::stoi(split[1]));
    };
    for (const auto& s : input) {
        auto split = split_string(s, " -> ");
        for (size_t i = 0; i < split.size()-1; ++i) {
            point p1(parse_point(split[i]));
            point p2(parse_point(split[i+1]));

            if (p1.first == p2.first) 
                for (auto j = std::min(p1.second, p2.second); j <= std::max(p1.second, p2.second); ++j) 
                    filled.insert(point(p1.first, j));
            else
                for (auto i = std::min(p1.first, p2.first); i <= std::max(p1.first, p2.first); ++i) 
                    filled.insert(point(i, p1.second)); 
        }
    }
}       

template <typename F>
bool day14::spawn_sand(std::unordered_set<point, hashes::PairHash<int,int>>& filled, F end_condition) {
    std::function<bool(point curPos)> step = [&](point curPos) {
        if (end_condition(curPos)) return false;
        else if (!filled.contains(point(curPos.first, curPos.second+1))) {
            return step(point(curPos.first, curPos.second+1));
        } else if (!filled.contains(point(curPos.first-1, curPos.second+1))) {
            return step(point(curPos.first-1, curPos.second+1));
        } else if (!filled.contains(point(curPos.first+1, curPos.second+1))) {
            return step(point(curPos.first+1, curPos.second+1));
        }
        filled.insert(curPos);
        return true;
    };
    return step(sandfall);
}

uint64_t day14::part_one() {
    uint64_t total = 0;
    auto filled_copy = filled;
    while (spawn_sand(filled_copy, [](point& p) {return p.second >= 200;})) total++;
    return total;
}

uint64_t day14::part_two() {
    uint64_t total = 0;
    auto filled_copy = filled;
    int maxDepth = 0;
    int maxWidth = 0;
    for (const auto& e : filled_copy) {
        maxDepth = std::max(maxDepth, e.second);
        maxWidth = std::max(maxWidth, e.first);
    }
    maxDepth += 2;
    for (int i = -maxDepth-2; i <= maxWidth+maxDepth-2; ++i)
        filled_copy.insert(point(i, maxDepth));

    while (spawn_sand(filled_copy, [&filled_copy](point& curPos){return filled_copy.contains(sandfall);})) total++;
    return total;
}

int main(int argc, char** argv) {
    day14 day14;
    std::cout << profile("Part one", [&day14](){return day14.part_one();}) << "\n";
    std::cout << profile("Part two", [&day14](){return day14.part_two();}) << "\n";
}