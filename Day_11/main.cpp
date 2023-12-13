#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cmath>
#define Part 2

struct Galaxy 
{
    int64_t x, y;
};

class Image
{
    std::vector<Galaxy> galaxies;
    std::unordered_set<size_t> emptyRows;
    std::unordered_set<size_t> emptyColums;

public:

    // contructor
    Image(std::vector<std::string> lines)
    {
        std::vector<bool> emptyCol(lines[0].size(), true);
        for(int64_t y = 0; y < lines.size(); y++)
        {
            bool emptyRow = true;
            for(int64_t x = 0; x < lines[y].size(); x++)
            {
                if(lines[y][x] == '#')
                {
                    galaxies.push_back({x, y});
                    emptyCol[x] = emptyRow = false;
                }
            }
            if(emptyRow)
                emptyRows.insert(y);
        }

        for(size_t x = 0; x < emptyCol.size(); x++)
        {
            if(emptyCol[x])
                this->emptyColums.insert(x);
        }
    }

    size_t sumAllPaths()
    {
        size_t sum = 0;
        for(size_t i = 0; i < galaxies.size(); i++)
        {
            for(size_t j = i + 1; j < galaxies.size(); j++)
            {
                const auto& g1 = galaxies[i];
                const auto& g2 = galaxies[j];
                sum += std::llabs(g1.x - g2.x) + std::llabs(g1.y - g2.y) 
                #if Part == 1
                + emptyRowsBetween(g1.y, g2.y) + emptyColumsBetween(g1.x, g2.x);
                #elif Part == 2
                + 999999 * (emptyRowsBetween(g1.y, g2.y) + emptyColsBetween(g1.x, g2.x));
                #endif
            }
        }
        return sum;
    }

    size_t emptyRowsBetween(size_t y1, size_t y2)
    {
        if(y1 > y2)
            std::swap(y1, y2);
        size_t count = 0;
        for(size_t y = y1 + 1; y < y2; y++)
        {
            if(emptyRows.find(y) != emptyRows.end())
                count++;
        }
        return count;
    }

    size_t emptyColsBetween(size_t x1, size_t x2)
    {
        if(x1 > x2)
            std::swap(x1, x2);
        size_t count = 0;
        for(size_t x = x1 + 1; x < x2; x++)
        {
            if(emptyColums.find(x) != emptyColums.end())
                count++;
        }
        return count;
    }
};

int main()
{
    std::ifstream file("input.txt");
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    Image image(lines);
    std::cout << image.sumAllPaths() << std::endl;
    file.close();
}