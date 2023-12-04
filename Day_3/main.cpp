#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdint.h>
#include <unordered_map>

int charToInt(char c);
std::vector<std::vector<bool>> genMask(std::vector<std::string> engineMap);
std::vector<std::vector<int>> genPairMask(std::vector<std::string> engineMap);
uint64_t engineValue(std::vector<std::string> engineMap, std::vector<std::vector<bool>> mask);
uint64_t engineGearsValue(std::vector<std::string> engineMap, std::vector<std::vector<int>> mask);

int main()
{
    // loading file
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> engineMap;
    while (std::getline(file, line))
    {
        engineMap.push_back(line);
    }

    // Part 1
    // std::vector<std::vector<bool>> mask = genMask(engineMap);
    // size_t sum = engineValue(engineMap, mask);

    // Part 2
    auto mask = genPairMask(engineMap);
    // for(int i = 0; i < mask.size(); ++i)
    // {
    //     for(int j = 0; j < mask[i].size(); ++j)
    //     {
    //         std::cout << mask[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << engineGearsValue(engineMap, mask) << std::endl;

}

// part 1
std::vector<std::vector<bool>> genMask(std::vector<std::string> engineMap)
{
    std::vector<std::vector<bool>> mask(engineMap.size(), std::vector<bool>(engineMap[0].size(), false));
    for (int i = 0; i < engineMap.size(); i++)
    {
        for (int j = 0; j < engineMap[i].size(); j++)
        {
            char c = engineMap[i][j];
            if ((c < '0' || c > '9') && c != '.') 
            {
                // convoltion
                if(i > 0)
                {
                    mask[i-1][j] = true;
                    if(j > 0) mask[i-1][j-1] = true;
                    if(j < engineMap[i].size()-1) mask[i-1][j+1] = true;
                }
                if(i < engineMap.size()-1)
                {
                    mask[i+1][j] = true;
                    if(j > 0) mask[i+1][j-1] = true;
                    if(j < engineMap[i].size()-1) mask[i+1][j+1] = true;
                }
                if(j > 0) mask[i][j-1] = true;
                if(j < engineMap[i].size()-1) mask[i][j+1] = true;
            }
            
        }
    }
    return mask;
}

uint64_t engineValue(std::vector<std::string> engineMap, std::vector<std::vector<bool>> mask)
{
    uint64_t sum = 0;
    for(int i = 0; i < engineMap.size(); ++i)
    {
        int num = 0;
        bool flag = false;
        for(int j = 0; j < engineMap[i].size(); ++j)
        {
            char c = engineMap[i][j];
            if(c >= '0' && c <= '9') 
            {
                num = num * 10 + charToInt(c);
                flag |= mask[i][j];
            }
            else
            {
                sum += num * flag;
                num = 0;
                flag = false;
            }
        }
        sum += num * flag;
    }
    return sum;
}

// part 2
std::vector<std::vector<int>> genPairMask(std::vector<std::string> engineMap)
{
    int n = 1;
    std::vector<std::vector<int>> mask(engineMap.size(), std::vector<int>(engineMap[0].size(), 0));
    for (int i = 0; i < engineMap.size(); i++)
    {
        for (int j = 0; j < engineMap[i].size(); j++)
        {
            char c = engineMap[i][j];
            if (c == '*') 
            {
                // convoltion
                if(i > 0)
                {
                    mask[i-1][j] += n;
                    if(j > 0) mask[i-1][j-1] += n;
                    if(j < engineMap[i].size()-1) mask[i-1][j+1] += n;
                }
                if(i < engineMap.size()-1)
                {
                    mask[i+1][j] += n;
                    if(j > 0) mask[i+1][j-1] += n;
                    if(j < engineMap[i].size()-1) mask[i+1][j+1] += n;
                }
                if(j > 0) mask[i][j-1] += n;
                if(j < engineMap[i].size()-1) mask[i][j+1] += n;
                ++n;
            }
        }
    }
    return mask;

}

uint64_t engineGearsValue(std::vector<std::string> engineMap, std::vector<std::vector<int>> mask)
{
    int sum = 0;
    std::unordered_map<int,int> multBuffer;
    for(int i = 0; i < engineMap.size(); ++i)
    {
        int num = 0;
        int pairNum = 0;
        for(int j = 0; j < engineMap[i].size(); ++j)
        {
            char c = engineMap[i][j];
            if(c >= '0' && c <= '9') 
            {
                num = num * 10 + charToInt(c);
                if(pairNum == 0)
                    pairNum = mask[i][j];
            }
            else
            {
                if(pairNum != 0)
                {
                    if(!multBuffer.contains(pairNum))
                        multBuffer[pairNum] = num;
                    else
                        sum += num * multBuffer[pairNum];
                }
                num = 0;
                pairNum = 0;
            }
        }
        if(pairNum != 0)
        {
            if(!multBuffer.contains(pairNum))
                multBuffer[pairNum] = num;
            else
                sum += num * multBuffer[pairNum];
        }
    }
    return sum;
}

int charToInt(char c)
{
    return c - '0';
}