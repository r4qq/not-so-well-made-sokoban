#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "defs.h"



struct targetPoint
{
    int x;
    int y;
};

class Level 
{
    std::vector<std::vector<char>> LevelMap; 
    bool IsDone;
    unsigned int StepCount;
    std::vector<targetPoint> Targets;
    targetPoint StartPos;
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

//i'm sorry i'm retarded
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

bool movePlayer(int dPX, int dPY, targetPoint pos, std::vector<std::vector<char>> currentMap)
{
    int newPosX = pos.x + dPX;
    int newPosY = pos.y + dPY;
    
    switch(currentMap[newPosX][newPosY])
    {
        default:
            break;
        case ' ':
            currentMap[pos.x][pos.y] = ' ';
            currentMap[newPosX][newPosY] = '@';
            break;
            
    }
     
}

void game(int x, int y, targetPoint StartPos, std::vector<targetPoint> targets, std::vector<std::vector<char>> levelMap)
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
                movePlayer(0, -1, StartPos, levelMap);
                break;
            case 'a':
                movePlayer(-1, 0, StartPos, levelMap);
                break;
            case 's':
                movePlayer(0, 1, StartPos, levelMap);
                break;
            case 'd':
                movePlayer(1, 0, StartPos, levelMap);
                break;
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