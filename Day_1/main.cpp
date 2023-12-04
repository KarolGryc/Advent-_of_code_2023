#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

int charToInt(char c)
{
    return c - '0';
}

int findFirstDigit(std::string & str)
{
    uint64_t index = UINT64_MAX;
    uint64_t value = 0;
    for(int i = 0; i < str.size(); ++i)
    {
        if(std::isdigit(str[i]))
        {
            value = charToInt(str[i]);
            index = i;
            break; 
        }
    }
    std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
                                      {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};
    for(auto & p : map)
    {
        uint64_t idx = str.find(p.second);
        if(idx < index)
        {
            index = idx;
            value = p.first;
        }
    }
    return value;
}

int findLastDigit(std::string & str)
{
    uint64_t index = 0;
    uint64_t value = 0;
    for(int i = str.size() - 1; i >= 0; --i)
    {
        if(std::isdigit(str[i]))
        {
            value = charToInt(str[i]);
            index = i;
            break; 
        }
    }
    std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"},
                                      {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};
    for(auto & p : map)
    {
        uint64_t idx = str.rfind(p.second);
        if(idx > index && idx != std::string::npos)
        {
            index = idx;
            value = p.first;
        }
    }
    return value;
}

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    uint64_t sum = 0;
    while(std::getline(in, line))
    {
        sum += findFirstDigit(line) *10 + findLastDigit(line);
    }
    std::cout << sum << std::endl;
    return 0;
}

// Jezus Maria ale syf