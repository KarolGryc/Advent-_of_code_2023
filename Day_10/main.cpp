#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

struct Point
{
    int64_t x;
    int64_t y;
};

enum Direction
{
    U,
    D,
    L,
    R
};

Point findStart(const std::vector<std::string> & map)
{
    for(int y = 0; map.size(); y++)
    {
        for(int x = 0; x < map[y].size(); x++)
        {
            if(map[y][x] == 'S')
            {
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

bool isValidPos(const std::vector<std::string> & map, const Point & position)
{
    return position.x > 0 && position.y > 0 && position.x < map[position.y].size() && position.y < map.size();
}

// std::ostream & operator<<(std::ostream & os, const Direction & dir)
// {
//     if(dir == U)
//         os << "UP";
//     else if(dir == D)
//         os << "DOWN";
//     else if(dir == L)
//         os << "LEFT";
//     else if(dir == R)
//         os << "RIGHT";
//     return os;
// }

// we are supposing that we rotation is correct
void rotateDirection(Direction& dir, char pipe)
{
    if(pipe == '|' || pipe == '-')
        return;
    if(pipe == 'L')
        dir = (dir == D) ? R : U;
    else if(pipe = 'J')
        dir = (dir == D) ? L : U;
    else if(pipe == '7')
        dir = (dir == U) ? L : D;
    else if(pipe == 'F')
        dir = (dir == U) ? R : D;
}

void movePosition(Point& pos, Direction dir)
{
    if(dir == U)
        pos.y--;
    else if(dir == D)
        pos.y++;
    else if(dir == L)
        pos.x--;
    else if(dir == R)
        pos.x++;
}

uint64_t loopLength(const std::vector<std::string> & map)
{

    uint64_t length = 0;
    Point pos = findStart(map);
    if(pos.x == -1)
        return 0;

    Direction dir;
    if(isValidPos(map, {pos.x, pos.y - 1}) && 
        (map[pos.y - 1][pos.x] == '|' || map[pos.y - 1][pos.x] == '7' || map[pos.y - 1][pos.x] == 'F')) 
        dir = U;
    else if(isValidPos(map, {pos.x, pos.y + 1}) && 
        (map[pos.y + 1][pos.x] == '|' || map[pos.y + 1][pos.x] == 'L' || map[pos.y + 1][pos.x] == 'J')) 
        dir = D;
    else if(isValidPos(map, {pos.x - 1, pos.y}) && 
        (map[pos.y][pos.x - 1] == '-' || map[pos.y][pos.x - 1] == 'L' || map[pos.y][pos.x - 1] == 'F')) 
        dir = L;
    else if(isValidPos(map, {pos.x + 1, pos.y}) && 
        (map[pos.y][pos.x + 1] == '-' ||  map[pos.y][pos.x + 1] == 'J' ||  map[pos.y][pos.x + 1] == '7')) 
        dir = R;
    else 
        return 0;

    do{
        movePosition(pos, dir);
        rotateDirection(dir, map[pos.y][pos.x]);
        length++;
    }while(map[pos.y][pos.x] != 'S');
    return length / 2;
}


int main()
{
    std::ifstream file("input.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    std::cout << loopLength(lines) << std::endl;
    return 0;
}