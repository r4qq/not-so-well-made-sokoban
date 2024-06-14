#include "Level.hpp"

Level::Level(std::vector<std::vector<char>> inMap, int inStepCount)
{
    LevelMap = inMap;
    IsDone = false;
    StepCount = inStepCount;
    GetStartPositionFromMap(LevelMap,StartPos);
    GetTargetsFromMap(LevelMap, Targets);
}

std::vector<std::vector<char>> Level::GetMap()
{
    return LevelMap;
}

int Level::GetStepCount()
{
    return StepCount;
}

std::vector<positionPoint> Level::GetTargets()
{
    return Targets;
}

positionPoint Level::GetStartPos()
{
        return StartPos;
}

void Level::GetTargetsFromMap(std::vector<std::vector<char>> Map, std::vector<positionPoint>& Targets)
{
for (auto i = 0; i < Map.size(); i++)
{
    for (auto j = 0; j < Map[i].size(); j++)
        {
            if (Map[i][j] == DOCK)
                Targets.push_back({ i, j });
        }
    }
}

void Level::GetStartPositionFromMap(std::vector<std::vector<char>> Map, positionPoint& StartPos)
{
    for (auto i = 0; i < Map.size(); i++)
    {
        for (auto j = 0; j < Map[i].size(); j++)
        {
            if (Map[i][j] == P0)
            {
                StartPos = { i, j };
                return;
            }
        }
    }  
}