#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Relation
{
    uint_fast32_t source;
    uint_fast32_t destination;
    size_t length;
};

Relation parseRelation(const std::string& line)
{
    std::istringstream lineStream(line);
    Relation rel;
    lineStream >> rel.destination >> rel.source >> rel.length;
    return rel;
}

uint_fast32_t checkLocation(uint_fast32_t seed,const std::vector<std::vector<Relation>> & allRelations)
{
    for(auto& relations : allRelations)
    {
        for(auto& rel : relations)
        {
            if(seed >= rel.source && seed < rel.source + rel.length)
            {
                seed = rel.destination + (seed - rel.source);
                break;
            }
        }
    }
    return seed;
}

uint_fast32_t minLocation(const std::vector<uint_fast32_t> & seeds, const std::vector<std::vector<Relation>>& allRelations)
{
    uint_fast32_t min = INT_MAX;
    for(auto& seed : seeds)
    {
        uint_fast32_t location = checkLocation(seed, allRelations);
        if(location < min)
            min = location;
    }
    return min;
}

uint_fast32_t minRangeLocation(const std::vector<uint_fast32_t>& seeds, std::vector<std::vector<Relation>>& allRelations)
{
    uint_fast32_t min = INT_MAX;
    for(int i = 0; i < seeds.size(); i+=2)
    {
        std::cout << "Calculating pair: " << seeds[i] << " " << seeds[i+1] << std::endl;
        size_t start = seeds[i];
        
        for(size_t seed = seeds[i]; seed < seeds[i] + seeds[i+1]; ++seed)
        {
            uint_fast32_t location = checkLocation(seed, allRelations);
            if(location < min)
                min = location;
        }
        std::cout << "Pair calculated! Min: " << min << '\n' <<  std::endl;
    }
    return min;
}

int main()
{

    std::ifstream file("input.txt");
    if(!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return -1;
    }

    std::string line;
    std::getline(file, line);
    std::istringstream seedsStream(line);
    seedsStream.ignore(10, ':');
    std::vector<uint_fast32_t> seeds;
    uint_fast32_t seed;
    while(seedsStream >> seed)
    {
        seeds.push_back(seed);
    }

    std::vector<std::vector<Relation>> allRelations;
    while (std::getline(file, line))
    {
        if(!line.empty() && line[0] < '0' || line[0] > '9')
        {
            allRelations.push_back(std::vector<Relation>());
            while(std::getline(file,line))
            {
                if(line.empty())
                    break;
                allRelations.back().push_back(parseRelation(line));
            }
        }
    }


    std::cout << minRangeLocation(seeds, allRelations) << std::endl;

    return 0;
}