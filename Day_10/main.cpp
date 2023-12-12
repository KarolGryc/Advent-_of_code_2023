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

char getPipeType(Direction startDir, Direction endDir)
{
    if(startDir == D && endDir == L || startDir == R && endDir == U)
        return 'F';
    else if(startDir == D && endDir == R || startDir == L && endDir == U)
        return '7';
    else if(startDir == U && endDir == R || startDir == L && endDir == D)
        return 'J';
    else if(startDir == U && endDir == L || startDir == R && endDir == D)
        return 'L';
    else if(startDir == U && endDir == D || startDir == D && endDir == U)
        return '|';
    else if(startDir == L && endDir == R || startDir == R && endDir == L)
        return '-';
    else
        return 'X';

}

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

std::ostream & operator<<(std::ostream & os, const Direction & dir)
{
    if(dir == U)
        os << "UP";
    else if(dir == D)
        os << "DOWN";
    else if(dir == L)
        os << "LEFT";
    else if(dir == R)
        os << "RIGHT";
    return os;
}

// we are supposing that we rotation is correct
void rotateDirection(Direction& dir, char pipe)
{
    if(pipe == '|' || pipe == '-')
        return;
    if(pipe == 'L')
        dir = (dir == D) ? R : U;
    else if(pipe == 'J')
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

    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
    do{
        movePosition(pos, dir);
        visited[pos.y][pos.x] = true;
        rotateDirection(dir, map[pos.y][pos.x]);
        length++;
    }while(map[pos.y][pos.x] != 'S');
    return length / 2;
}

uint64_t areaEnclosed(std::vector<std::string> & map)
{
    Point pos = findStart(map);
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

    Direction startDir = dir;
    
    // finding loop
    std::vector<std::vector<bool>> loopElement(map.size(), std::vector<bool>(map[0].size(), false));
    do{
        movePosition(pos, dir);
        loopElement[pos.y][pos.x] = true;
        rotateDirection(dir, map[pos.y][pos.x]);
    }while(map[pos.y][pos.x] != 'S');

    // changing S to pipe
    map[pos.y][pos.x] = getPipeType(startDir, dir);

    uint64_t count = 0;
    for(int y = 0; y < map.size(); y++)
    {
        for(int x = 0; x < map[y].size(); x++)
        {
            if(loopElement[y][x])
                continue;

            bool inside = false;
            for(int dx = x; dx >= 0; dx--)
            {
                const char& curr = map[y][dx]; 
                if(loopElement[y][dx] && (curr == '|' || curr == 'F' || curr == '7' ))
                    inside = !inside;
            }
            if(inside)
                count++;
        }
    }
    return count;
}

// code above needs to be refactored
int main()
{
    std::ifstream file("test.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    // part 1
    // std::cout << loopLength(lines) << std::endl;
    // part 2
    std::cout << areaEnclosed(lines);
    return 0;
}