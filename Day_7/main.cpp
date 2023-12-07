#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#define PART2 1


enum class HandType
{
    highCard = 1,
    onePair = 2,
    twoPairs = 3,
    threeOfAKind = 4,
    fullHouse = 5,
    fourOfAKind = 6,
    fiveOfAKind = 7
};

std::unordered_map<char, int> cardValues = {
    #if PART2
    {'J', 1},
    #else
    {'J', 11},
    #endif
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};
struct Hand
{
    HandType type;
    std::string cards;
    int bid;
    bool operator<(const Hand& other) const
    {
        Hand a = *this;
        Hand b = other;
            // all Hand are different
            if (a.type != b.type)
            {
                return a.type < b.type;
            }
            else
            {
                constexpr int handSize = 5;
                for (int i = 0; i < handSize; i++)
                {
                    if (a.cards[i] != b.cards[i])
                    {
                        return cardValues[a.cards[i]] < cardValues[b.cards[i]];
                    }
                }
                return false;
            };
    }
};

HandType checkType(const std::string& cards)
{
    std::unordered_map<char, int> cardCount;
    for (char c : cards)
    {
        cardCount[c]++;
    }
    
    int maxCount = 0;
    for (auto& pair : cardCount)
    {
        #if PART2
        if(pair.first == 'J')
            continue;
        #endif
        maxCount = std::max(maxCount, pair.second);
    }
    #if PART2
    maxCount += cardCount['J'];
    cardCount.erase('J');
    #endif
    switch (maxCount)
    {
        case 1:
            return HandType::highCard;
        case 2:
            return cardCount.size() == 4 ? (HandType::onePair) : (HandType::twoPairs);
        case 3:
            return cardCount.size() == 3 ? (HandType::threeOfAKind) : (HandType::fullHouse);
        case 4:
            return HandType::fourOfAKind;
        case 5:
        case 10: // case JJJJJ )()
            return HandType::fiveOfAKind;
        default:
            return HandType::highCard;
    }
}

int main()
{
    std::ifstream file("input.txt");
    std::string line;
    std::priority_queue<Hand> hands;
    while(std::getline(file, line))
    {
        int bid;
        std::string cards;
        std::istringstream ss(line);
        ss >> cards >> bid;
        hands.push({checkType(cards), cards, bid});
    }
    std::cout << std::endl;

    uint64_t sum = 0;
    while(hands.size() > 0)
    {
        sum += hands.top().bid * hands.size();
        std::cout << hands.top().cards << " " << (int)hands.top().type << " " << hands.top().bid << "*" << hands.size() << " = " << hands.top().bid * hands.size() << std::endl;
        hands.pop();
    }
    std::cout << std::endl << sum;
}