#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#define PART 2
int64_t nextValue(const std::vector<int64_t>& values)
{
    std::vector<int64_t> diffs;
    bool allZeros = true;
    for(int i = 1; i < values.size(); ++i)
    {
        diffs.push_back(values[i] - values[i - 1]);
        allZeros &= (diffs.back() == 0);
    }
    if(allZeros)
        return values.back();
    else
        return values.back() + nextValue(diffs);
}

std::vector<int64_t> getValuesFromLine(const std::string & line)
{
    std::vector<int64_t> values;
    std::stringstream ss(line);
    int64_t val;
    while(ss >> val)
        values.push_back(val);
    return values;
}

int main()
{
    std::ifstream file("input.txt");
    std::string line;
    int64_t sum = 0;
    while (std::getline(file, line))
    {
        #if PART == 1
        auto n = nextValue(getValuesFromLine(line));
        #elif PART == 2
            auto vec = getValuesFromLine(line);
            std::reverse(vec.begin(), vec.end());
            auto n = nextValue(vec);
        #endif
        sum += n;
        // It is possible to do it in more efficient way
        // but it is not necessary for this input
    }
    std::cout << sum << std::endl;
    return 0;
}