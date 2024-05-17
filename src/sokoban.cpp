#include <cstdlib>
#include <iostream>
#include <vector>
#include <conio.h>

#include "./Level.hpp"

bool isLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks)
{
    int doneBoxes = 0;
    for (int i = 0; i < docks.size(); i++)
    {
        if (levelMap[docks[i].x][docks[i].y] == DBOX)
            doneBoxes++;
    }
    if (doneBoxes == docks.size())
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
    std::cout << "------------------------" << '\n';
    std::cout << stepCount << '\n';
}

void renderDebugMenu(positionPoint& pos)
{
    std::cout << "------------------------" << '\n';
    std::cout << "ddddd" << '\n';
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
            levelDone = true;
    }
}

int main()
{
    //test level data
    std::vector<std::vector<char>> maplevel
    {
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

    //test level
    Level TestLevel(maplevel, 40);


    //main game loop
    game(TestLevel.GetStartPos(), TestLevel.GetMap(), TestLevel.GetTargets(), TestLevel.GetStepCount());

    return 0;
}