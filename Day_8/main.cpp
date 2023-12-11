#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <numeric>
#define PART 2

struct Directions
{
    std::string left;
    std::string right;
};

uint64_t roadLength(const std::string& directions, 
    const std::unordered_map<std::string, Directions>& map, 
    const std::string& startNode = "AAA"
)
{
    uint64_t length = 0;
    std::string currNode = startNode;
    while(1){
        for (size_t i = 0; i < directions.size(); ++i)
        {
            if(currNode.back() == 'Z')
                return length;

            if(directions[i] == 'L')
                currNode = map.at(currNode).left;
            else if(directions[i] == 'R')
                currNode = map.at(currNode).right;
            ++length;
        }
    }
    return length;
}

uint64_t roadLengthGhost(const std::string& directions, 
    const std::unordered_map<std::string, Directions>& map, 
    std::vector<std::string> startingNodes
)
{
    uint64_t length = 1;
    for(auto& node: startingNodes)
    {
        length = std::lcm(length, roadLength(directions, map, node));
    }
    return length;
}


int main()
{
    std::ifstream file("input.txt");
    if(!file.is_open())
        return -1;

    // getting directions
    std::string directions;
    std::getline(file, directions);

    // loading map
    std::string line;
    std::unordered_map<std::string, Directions> map;
    std::vector<std::string> startingNodes;
    while (std::getline(file, line))
    {
        if(line.empty())
            continue;
        std::istringstream iss(line);
        std::string key, left, right;
        iss >> key;
        if(key.back() == 'A')
            startingNodes.push_back(key);
        iss.ignore(INT_MAX, '(');
        iss >> left >> right;
        left.pop_back();
        right.pop_back();
        map[key] = {left, right};
    }
    #if PART == 1
    std::cout << roadLength(directions, map) << std::endl;
    #elif PART == 2
    std::cout << "Length: " << std::flush << roadLengthGhost(directions, map, startingNodes);
    #endif
    return 0;
}