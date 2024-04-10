#include <iostream>
#include <vector>
//#include <algorithm>
#include <conio.h>
#include "defs.h"



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
       Level(std::vector<std::vector<char>> inMap)
       {
            LevelMap = inMap;
       }
       std::vector<std::vector<char>> GetMap()
       {
            return LevelMap;
       }
};

bool isLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks)
{
    auto docksAmount = docks.size();
    auto x = 0;
    for (auto i = 0; i < docksAmount; i++)
    {
        if (levelMap[docks[i].x][docks[i].y] == DBOX)
            x++;
    }
    bool isDone = (x == docksAmount) ? true : false;
    return isDone; 
}

void renderLevel(std::vector<std::vector<char>> levelMap)
{
    int levelWidth = levelMap.size();
    int levelHeight = levelMap[0].size();
    
    for(auto i = 0; i < levelWidth; i++)
    {
        for(auto j = 0; j < levelHeight; j++)
        {
            std::cout << levelMap[i][j];
        }    
        std::cout << "\n";
    }
}

void movePlayer(int dPX, int dPY, positionPoint pos, std::vector<std::vector<char>> currentMap)
{
    int newPosX = pos.x + dPX;
    int newPosY = pos.y + dPY;
    
    switch(currentMap[newPosX][newPosY])
    {
        default:
            break;

        case AIR:
            currentMap[pos.x][pos.y] = AIR;
            currentMap[newPosX][newPosY] = P0;
            pos.x = newPosX;
            pos.y = newPosY;
            break;
        case BOX:
            switch (currentMap[newPosX + 1][newPosX + 1]) 
            {
                default:
                    break;
                case BOX:
                    break;
                case WALL:
                    break;  
                case AIR:
                    currentMap[newPosX + 1][newPosY + 1] = BOX;
                    currentMap[newPosX][newPosY] = P0;
                    currentMap[pos.x][pos.y] = AIR;
                    break;
                case DOCK:
                    break;
            }
    }
}

void game(positionPoint StartPos, std::vector<positionPoint> targets, std::vector<std::vector<char>> levelMap, std::vector<positionPoint> doneBoxes)
{
    positionPoint pozycja = StartPos;
    bool isLevelDone = false;
    while (isLevelDone != true)
    {
        system("cls");
        renderLevel(levelMap);
        char movement;
        while(movement != 'm')
        {
            movement = getch();
            switch(movement)
            {
                default:
                    std::cout << "invalid move" << '\n';
                    break;
                case 'w':
                    movePlayer(0, -1, pozycja, levelMap);
                    break;
                case 'a':
                    movePlayer(-1, 0, pozycja, levelMap);
                    break;
                case 's':
                    movePlayer(0, 1, pozycja, levelMap);
                    break;
                case 'd':
                    movePlayer(1, 0, pozycja, levelMap);
                    break;
            }
        }        
    }
}



int main()
{
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
        
    Level poz1(maplevel);
    //renderLevel(poz1.GetMap());
       
    return 0;
}