#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

std::vector<Color> parseLine(std::string & arg)
{
    std::stringstream ss(arg);
    std::vector<Color> results;
    int val;
    std::string type;
    Color added = {0,0,0};
    ss.ignore(INT32_MAX, ':');
    while(ss >> val >> type){
        if(type[0] == 'r') added.r = val;
        else if(type[0] == 'g') added.g = val;
        else if(type[0] == 'b') added.b = val;
        if(type.back() == ';') {
            results.push_back(added);
            added = {0,0,0};
        }
    }
    results.push_back(added);
    return results;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    uint64_t sum = 0;
    while(std::getline(in, line))
    {
        auto colors = parseLine(line);
        int minr = 0, ming = 0, minb = 0;
        for(auto & color: colors)
        {
            if(color.r > minr) minr = color.r;
            if(color.g > ming) ming = color.g;
            if(color.b > minb) minb = color.b;
        }
        sum += minr * ming * minb;
    }
    std::cout << sum;
}