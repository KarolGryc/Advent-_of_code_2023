#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

struct Game
{
    std::unordered_set<uint64_t> winNums;
    std::unordered_set<uint64_t> pickedNums;
};

Game parseLine(std::string line);
uint64_t gameValue(Game game);
uint64_t calculateDuplicates(const std::vector<int> & arg);
uint64_t wonGames(Game game);

int main()
{
    // part 1
    std::ifstream input("input.txt");
    std::vector<int> winsInGame;
    std::string line;
    int sum = 0;
    while (std::getline(input, line))
    {
        Game game = parseLine(line);
        winsInGame.push_back(wonGames(game));
        sum += gameValue(game);

    }
    std::cout << "Part 1: " << sum << '\n';

    // part 2
    
    std::cout << "Part 2: " << calculateDuplicates(winsInGame) << '\n'; 

    return 0;
}

uint64_t wonGames(Game game)
{
    uint64_t count = 0;
    for(auto num : game.winNums)
    {
        count += game.pickedNums.contains(num);
    }
    return count;
}

uint64_t gameValue(Game game)
{
    return 1 << (wonGames(game) - 1);
}

uint64_t calculateDuplicates(const std::vector<int> & vec)
{
    // vec contains the number of winning numbers in each game
    std::vector<int> duplicates(vec.size(),1);
    const size_t size = vec.size();
    for(int i = 0; i < size; i++)
    {
        for(int j = i+1; j < size && j <= i + vec[i] ; j++)
        {
            duplicates[j] += duplicates[i];
        }
    }
    uint64_t sum = 0;
    for(auto num : duplicates)
    {
        sum += num;
    }
    return sum;
}

Game parseLine(std::string line)
{
    Game game;
    std::istringstream ss(line);
    ss.ignore(INT_MAX, ':');

    while(true)
    {
        std::string inp;
        ss >> inp;
        if(inp == "|") break;
        game.winNums.insert(std::stoull(inp));
    }

    while(true)
    {
        std::string inp;
        ss >> inp;
        if(!ss) break;
        game.pickedNums.insert(std::stoull(inp));
    }
    return game;
}