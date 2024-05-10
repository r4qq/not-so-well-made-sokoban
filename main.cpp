#include <cstdlib>
#include <iostream>
#include <vector>
#include <conio.h>
#include "defs.hpp"

struct positionPoint
{
    int x;
    int y;
};

class Level
{
    std::vector<std::vector<char>> LevelMap;
    bool IsDone;
    unsigned int StepCount;
    std::vector<positionPoint> Targets;
    positionPoint StartPos;
public:
    Level(std::vector<std::vector<char>> inMap, int inStepCount, std::vector<positionPoint> inTargets, positionPoint inStartPos)
    {
        LevelMap = inMap;
        IsDone = false;
        StepCount = inStepCount;
        Targets = inTargets;
        StartPos = inStartPos;
    }
    std::vector<std::vector<char>> GetMap()
    {
        return LevelMap;
    }
    int GetStepCount()
    {
        return StepCount;
    }
    std::vector<positionPoint> GetTargets()
    {
        return Targets;
    }
    positionPoint GetStartPos()
    {
        return StartPos;
    }
};

bool isLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks)
{
    int docksAmount = docks.size();
    int x = 0;
    for (auto i = 0; i < docksAmount; i++)
    {
        if (levelMap[docks[i].x][docks[i].y] == DBOX)
        {
            x++;
        }

    }
    if (x == docksAmount) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void renderLevel(std::vector<std::vector<char>> levelMap, int stepCount)
{
    int levelWidth = levelMap.size();
    int levelHeight = levelMap[0].size();

    for (auto i = 0; i < levelWidth; i++)
    {
        for (auto j = 0; j < levelHeight; j++)
        {
            std::cout << levelMap[i][j];
        }
        std::cout << "\n";
    }
    std::cout << stepCount << '\n';
}

void renderDebugMenu(positionPoint& pos)
{
    std::cout << "x: " << pos.x + 1 << '\n';
    std::cout << "y: " << pos.y + 1 << '\n';
}

void movePlayer(int dPX, int dPY, positionPoint& pos, std::vector<std::vector<char>>& currentMap, int& stepCount)
{
    int newPosX, newPosY;
    newPosX = pos.x + dPX;
    newPosY = pos.y + dPY;
    bool movementMade = false;

    switch (currentMap[newPosX][newPosY])
    {
    default:
        break;
    
    case AIR:
        currentMap[pos.x][pos.y] = AIR;
        currentMap[newPosX][newPosY] = P0;
        movementMade = true;
        break;
    case BOX:
        switch (currentMap[newPosX + dPX][newPosY + dPY])
        {
        default:
            break;
        case BOX:
            break;
        case AIR:
            currentMap[pos.x][pos.y] = AIR;
            currentMap[newPosX][newPosY] = P0;
            currentMap[newPosX + dPX][newPosY + dPY] = BOX;
            movementMade = true;
            break;
        case DOCK:
            currentMap[pos.x][pos.y] = AIR;
            currentMap[newPosX][newPosY] = P0;
            currentMap[newPosX + dPX][newPosY + dPY] = DBOX;
            movementMade = true;
            break;
        }
    }
    if (movementMade)
    {
        pos.x = newPosX;
        pos.y = newPosY;
        stepCount--;
    }
}

void game(positionPoint startPos, std::vector<std::vector<char>> levelMap, std::vector<positionPoint> doneBoxes, int stepCount)
{
    bool levelDone = false;
    char movement = NULL;
    while (!levelDone)
    {
        system("cls");
        renderLevel(levelMap, stepCount);
        renderDebugMenu(startPos);
        movement = _getch();
        switch (movement)
        {
        default:
            std::cout << "invalid move" << '\n';
            break;
        case 'w':
            movePlayer(-1, 0, startPos, levelMap, stepCount);
            levelDone = isLeveDone(levelMap, doneBoxes);
            break;
        case 'a':
            movePlayer(0, -1, startPos, levelMap, stepCount);
            levelDone = isLeveDone(levelMap, doneBoxes);
            break;
        case 's':
            movePlayer(1, 0, startPos, levelMap, stepCount);
            levelDone = isLeveDone(levelMap, doneBoxes);
            break;
        case 'd':
            movePlayer(0, 1, startPos, levelMap, stepCount);
            levelDone = isLeveDone(levelMap, doneBoxes);
            break;
        case 'm':
            levelDone = true;
        }
        if (stepCount == 0) 
        {
            levelDone = true;
        }
    }
}

int main()
{
    //test level data
    positionPoint pozycjaStartowa;
    pozycjaStartowa.x = 5;
    pozycjaStartowa.y = 4;
    std::vector<std::vector<char>> maplevel{
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*',' ',' ','*','*','*','*'},
        {'*','*','*','X',' ','#','*','*','*','*'},
        {'*','*','*',' ',' ',' ',' ','*','*','*'},
        {'*','*','X',' ','@',' ',' ','*','*','*'},
        {'*','*','*',' ','#','*','*','*','*','*'},
        {'*','*','*',' ',' ','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'}
    };

    std::vector<positionPoint> targety{
        {3, 3},
        {2, 5}
    };
    
    Level poz1(maplevel, 30, targety, pozycjaStartowa);


    //main game loop
    game(poz1.GetStartPos(), poz1.GetMap(), poz1.GetTargets(), poz1.GetStepCount());

    return 0;
}