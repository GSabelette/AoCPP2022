#include "day10.hpp"

day10::day10() {
    instructions = profile("Opening file", readFile, "inputs/day10.input");
}

int runInstruction(const std::string& instruction, int& clock , int& regX) {
    int retVal = 0;
    clock +=1;
    retVal = (clock%40 == 20) ? regX*clock : 0;
    if (instruction != "noop") {
        clock += 1;
        if (clock%40 ==20) retVal = regX*clock;
        regX += std::stoi(split_string(instruction, " ")[1]);
    }
    return retVal;
}

int day10::part_one() {
    int clock = 0;
    int regX = 1;
    int sum = 0;
    for (auto& instruction : instructions) {
        sum += runInstruction(instruction, clock, regX);
    }
    return sum;
}

screen day10::part_two() {
    screen screen;
    int clock = 0;
    int regX = 1;
    auto draw = [](int clock, int regX) {return ((clock%40) >= regX-1 && (clock%40) <= regX+1) ? '#' : '.';};
    for (auto& instruction : instructions) {
        //std::cout << clock << " | " << regX;
        screen[clock/40].push_back(draw(clock, regX));
        clock += 1;
        if (instruction != "noop") {
            screen[clock/40].push_back(draw(clock, regX));
            clock += 1;
            regX += std::stoi(split_string(instruction, " ")[1]);
        }
    }
    return screen;
}

int main(int argc, char** argv) {
    day10 day10;
    std::cout << profile("Part one", [&day10](){return day10.part_one();}) << "\n";
    auto screen = profile("Part two", [&day10](){return day10.part_two();});
    for (const auto& line : screen) std::cout << line << "\n";
}