#include "day13.hpp"

#define EOP 0

day13::day13() {
    auto input = profile("Opening file", readFile, "inputs/day13.input");
    packetPair curPair;
    bool first = true;
    for (const auto& s : input) {
        if (s.empty()) {
            packetPairs.push_back(curPair);
        } else {
            if (first) 
                curPair.first = s;
            else curPair.second = s;
            first = 1 - first;
        }
    }
    packetPairs.push_back(curPair);
}

// std::string readPacket(std::string packet, int index) {
//     int endIndex = index;
//     for (const auto& c : packet.substr(index)) {
//         if (c == '[');
//     }
// }

std::vector<int> subPacketsIndexes(std::string s) {
    std::vector<int> indexes;
    int depth = 0;
    for (size_t index = 1; index < s.size(); ++index) {
        char c = s[index];
        if (c == '[') {
            if (depth == 0) indexes.push_back(index);
            depth++;
        }
        else if (c == ']') {
            depth--;
            if (depth == 0) indexes.push_back(index+1);
        }
        index++;
    }
    return indexes;
}

std::vector<std::string> getSubPackets(std::string s) {
    std::vector<std::string> subpackets;
    auto spi = subPacketsIndexes(s);
    subpackets.push_back(s.substr(0, spi.front()));
    for (size_t i = 0; i < spi.size()-1; ++i)
        subpackets.push_back(s.substr(spi[i], spi[i+1]-spi[i]));
    subpackets.push_back(s.substr(spi.back()));
    return subpackets;
}

std::tuple<int, size_t, int> getNextNumber(const std::string& s, size_t i) {
    bool depthDiff = false;
    for (size_t index = i+1; index < s.size(); ++index) {
        if (s[index] == '[') depthDiff = true;
        if (s[index] == ']') depthDiff = true;
        if (std::isdigit(s[index])) {
            if (std::isdigit(s[index+1])) {
                return std::make_tuple(std::stoi(s.substr(index,2)), index+1, depthDiff);
            } else return std::make_tuple(s[index] - '0', index, depthDiff);
        }
    }
    return std::make_tuple(EOP, 0, 0);
}

bool isSorted(packetPair p) {
    auto t1 = getNextNumber(p.first, 0);
    auto t2 = getNextNumber(p.second, 0);
    if (std::get<0>(t1) != std::get<0>(t2)) return (std::get<0>(t1) < std::get<0>(t2));
    while (std::get<0>(t1) != EOP && std::get<0>(t2) != EOP) {
        //std::cout << "Chars " << std::get<0>(t1) << " | " << std::get<0>(t2) << "\n";
        //std::cout << "Indexes " << std::get<1>(t1) << " | " << std::get<1>(t2) << "\n";
        t1 = getNextNumber(p.first, std::get<1>(t1));
        t2 = getNextNumber(p.second, std::get<1>(t2));
        
        std::cout << "DepthDiffs : " << std::get<2>(t1) << " | " << std::get<2>(t2) << "\n";

        //std::cout << std::get<0>(t1) << " | " << std::get<0>(t2) << "\n";


        if (std::get<0>(t1) != std::get<0>(t2)) {
            std::cout << "OVER : " << std::get<0>(t1) << " | " << std::get<0>(t2) << "\n";
            return (std::get<0>(t1) < std::get<0>(t2));
        }

        // If Left changed scope but not Right it ran out of numbers.
        if (std::get<2>(t1) && !std::get<2>(t2)) {
            std::cout << "LEFT RAN OUT\n";
            return true;
        }
        if (std::get<2>(t2) && !std::get<2>(t1)) {
            std::cout << "RIGHT RAN OUT\n";
            return false;
        }
    }
    std::cout << "EOP\n";
    return (std::get<0>(t2) != EOP);
}

int day13::part_one() {
    int sum = 0;
    for (int i = 0; i < packetPairs.size(); ++i) {
        std::cout << "Packet : " << packetPairs[i] << "\n";
        if (isSorted(packetPairs[i])) {
            std::cout << "Packet : " << packetPairs[i] << " is sorted\n";
            sum += i+1;
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    day13 day13;
    std::cout << day13.part_one() << "\n";
    //std::cout << isSorted(day13.packetPairs[0]) <<"\n";
    // for (const auto& pair : day13.packetPairs) {
    //     std::cout << pair << " | "<< isSorted(pair) << "\n";
    // }
    // std::string s = "[[1],[2,3,4]]";
    // std::cout << "nb subpackets : "<< getSubPackets(s).size() << "\n";
    // for (auto& sp : getSubPackets(s)) {
    //     std::cout << sp << "\n";
    //     std::cout << getSubPackets(sp).size() << "\n";
    // }
}