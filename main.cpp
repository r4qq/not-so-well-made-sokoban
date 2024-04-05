#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "defs.h"

void movePlayer(int x, int y)
{
    
}

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



void game(int x, int y, targetPoint StartPos, std::vector<targetPoint> targets)
{
    system("cls");
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
                movePlayer(0, -1);
                break;
            case 'a':
                movePlayer(-1, 0);
                break;
            case 's':
                movePlayer(0, 1);
                break;
            case 'd':
                movePlayer(1, 0);
                break;
        }
    }
}

//i'm sorry i'm retarded
void renderLevel(std::vector<std::vector<char>> LevelMap)
{
    int levelWidth = LevelMap.size();
    int levelHeight = LevelMap[0].size();
    
    for(auto i = 0; i < levelWidth; i++)
    {
        for(auto j = 0; j < levelHeight; j++)
        {
            std::cout << LevelMap[i][j];
        }    
        std::cout << "\n";
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
    renderLevel(poz1.GetMap());
       
    return 0;
}