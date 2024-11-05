
#include "Game.hpp"
#include "Level.hpp"

#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <vector>

Game::Game(void)
{
    InitalizeGame();
}

void Game::InitalizeGame(void)
{
    AddLevels();
    DrawMenu();
}

std::vector<Level> Game::GetLevels(void)
{
    return LevelList;
}

void Game::AddLevels(void)
{
    std::vector<std::vector<char>> TestMap1 =
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
    int Teststeps1 = 40;

    std::vector<std::vector<char>> TestMap2 =
    {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*',' ',' ',' ','*','*','*'},
        {'*','*','*','*','#','*',' ','*','*','*'},
        {'*','*','*','X',' ',' ','P','*','*','*'},
        {'*','*',' ',' ',' ','*','*','*','*','*'},
        {'*','*',' ','#',' ',' ',' ','X','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','*','*','*','*','*','*','*','*','*'}
    };
    int Teststeps2 = 21;

    Level TestLevel1(TestMap1, Teststeps1);
    Level TestLevel2(TestMap2, Teststeps2);

    LevelList.push_back(TestLevel1);
    LevelList.push_back(TestLevel2);
}

void Game::DrawBanner(void)
{
    std::cout << "       .dMMMb  .aMMMb  dMP dMP .aMMMb  dMMMMb  .aMMMb  dMMMMb" << '\n'; 
    std::cout << "      dMP\" VP dMP\"dMP dMP.dMP dMP\"dMP dMP\"dMP dMP\"dMP dMP dMP" << '\n'; 
    std::cout << "      VMMMb  dMP dMP dMMMMK\" dMP dMP dMMMMK\" dMMMMMP dMP dMP" << '\n';  
    std::cout << "    dP .dMP dMP.aMP dMP\"AMF dMP.aMP dMP.aMF dMP dMP dMP dMP" << '\n';   
    std::cout << "    VMMMP\"  VMMMP\" dMP dMP  VMMMP\" dMMMMP\" dMP dMP dMP dMP" << '\n';    
                                                          
}

void Game::DrawMenu(void)
{
   system("cls");
   unsigned int wybor;
   DrawBanner();
   std::cout  << '\n';
   for (int i = 0; i < (int)LevelList.size(); i++) 
   {
        std::cout << "    " << "Poziom " << i + 1 << '\n'; 
   }     
   std::cout << '>';
   std::cin >> wybor;
   switch (wybor) 
   {
    case 0:
        return;
    default: 
        if ((wybor - 1 > (int)LevelList.size())) 
        { 
            std::cout << "Nie ma takiego wyboru" << '\t';
            DrawMenu();
        }
        else 
        {
            GameLoop(LevelList[wybor - 1].GetStartPos(), LevelList[wybor - 1].GetMap(), LevelList[wybor - 1].GetTargets(), LevelList[wybor - 1].GetStepCount());
        }
        break;
   }
}

void Game::PlayerMovement(int dPX, int dPY, positionPoint &pos, std::vector<std::vector<char>> &currentMap, int &stepCount)
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

 void Game::GameLoop(positionPoint startPos, std::vector<std::vector<char>> levelMap, std::vector<positionPoint> doneBoxes, int stepCount)
 {
    bool levelDone;
    char movement = NULL;
    while (true)
    {
        system("cls");
        RenderLevelDebug(levelMap, stepCount);
        RenderDebugMenu(startPos);
        movement = _getch();
        switch (movement)
        {
        default:
            std::cout << "invalid move" << '\n';
            break;
        case 'w':
            PlayerMovement(-1, 0, startPos, levelMap, stepCount);
            levelDone = IsLeveDone(levelMap, doneBoxes);
            break;
        case 'a':
            PlayerMovement(0, -1, startPos, levelMap, stepCount);
            levelDone = IsLeveDone(levelMap, doneBoxes);
            break;
        case 's':
            PlayerMovement(1, 0, startPos, levelMap, stepCount);
            levelDone = IsLeveDone(levelMap, doneBoxes);
            break;
        case 'd':
            PlayerMovement(0, 1, startPos, levelMap, stepCount);
            levelDone = IsLeveDone(levelMap, doneBoxes);
            break;
        case 'm':
            levelDone = true;
        }
        if (stepCount == 0)
            levelDone = true;
    }
 }

bool Game::IsLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks)
{
    int doneBoxes = 0;
    for (int i = 0; i < (int)docks.size(); i++)
    {
        if (levelMap[docks[i].x][docks[i].y] == DBOX)
            doneBoxes++;
    }
    if (doneBoxes == (int)docks.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::RenderLevelDebug(std::vector<std::vector<char>> levelMap, int stepCount)
{
    for (auto i = 0; i < (int)levelMap.size(); i++)
    {
        for (auto j = 0; j < (int)levelMap[0].size(); j++)
        {
            std::cout << levelMap[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "------------------------" << '\n';
    std::cout << "Steps: " << stepCount << '\n';
    std::cout << "------------------------" << '\n';
}

void Game::RenderDebugMenu(positionPoint &pos)
{
    std::cout << "ddddd" << '\n';
    std::cout << "x: " << pos.x + 1 << '\n';
    std::cout << "y: " << pos.y + 1 << '\n';
}


