#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <iomanip>

struct Race
{
    uint64_t time;
    uint64_t distance;
};

bool isInt(double d)
{
    // the same as return d - (int) d == 0;
    return std::fmod(d, 1) == 0;
}

uint64_t waysToWinRace(uint64_t maxT, uint64_t minD)
{
    double delta = std::sqrt(maxT * maxT - 4 * minD);
    double x2 = (maxT + delta) / 2;
    double x1 = (maxT - delta) / 2;
    x2 = isInt(x2) ? (x2 - 1) : (std::floor(x2));
    x1 = isInt(x1) ? (x1 + 1) : (std::ceil(x1));
    return x2 - x1 + 1;
}

uint64_t waysToWinRaces(const std::vector<Race>& races)
{
    uint64_t possibleWays = 1;
    for(auto & e: races)
    {
        possibleWays *= waysToWinRace(e.time, e.distance);
    }
    return possibleWays;
}


int main()
{
    std::ifstream file("input.txt");
    if(!file.is_open())
    {
        std::cout << "File not found!";
        return -1;
    }

    std::vector<Race> races;
    std::string times, distnaces;
    std::getline(file, times);
    std::getline(file, distnaces);
    file.close();

    std::istringstream tms(times);
    std::istringstream dst(distnaces);
    tms.ignore(INT_MAX, ':');
    dst.ignore(INT_MAX, ':');
    uint64_t t, d;
    while(tms >> t && dst >> d)
    {
        races.push_back({t, d});
    }

    // Part 1
    std::cout << "Ways to win: " << waysToWinRaces(races) << std::endl;

    // Part 2
    std::istringstream longTime(times);
    std::istringstream longDist(distnaces);
    longTime.ignore(INT_MAX, ':');
    longDist.ignore(INT_MAX, ':');
    std::string longT, longD, temp;
    while(longTime >> temp) longT += temp;
    while(longDist >> temp) longD += temp;
    std::cout << "Ways to win long race: "<< waysToWinRace(std::stoull(longT), std::stoull(longD));

}