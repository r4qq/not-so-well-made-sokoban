#pragma once

#include "sokoban.hpp"

#include <vector>

class Level
{
    std::vector<std::vector<char>> LevelMap;
    bool IsDone;
    unsigned int StepCount;
    std::vector<positionPoint> Targets;
    positionPoint StartPos;
    
public:
    Level(std::vector<std::vector<char>> inMap, int inStepCount);
    std::vector<std::vector<char>> GetMap(void);
    int GetStepCount(void);
    std::vector<positionPoint> GetTargets(void);
    positionPoint GetStartPos(void);

private:
    void GetTargetsFromMap(std::vector<std::vector<char>> Map, std::vector<positionPoint> &Targets);
    void GetStartPositionFromMap(std::vector<std::vector<char>> Map, positionPoint &StartPos);
};