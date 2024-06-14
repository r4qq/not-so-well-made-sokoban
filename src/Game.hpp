#include "Level.hpp"
#include <vector>

class Game
{
    std::vector<Level> LevelList;
public:
    Game();
    void InitalizeGame();
    void PlayGame();
    //void SetLevels(std::vector<std::vector<char>> maplevel, int stepCount);
    std::vector<Level> GetLevels();
private:
    void DrawBanner();
    void AddLevels();
    void DrawMenu();
    void PlayerMovement(int dPX, int dPY, positionPoint& pos, std::vector<std::vector<char>>& currentMap, int& stepCount);
    void GameLoop(positionPoint startPos, std::vector<std::vector<char>> levelMap, std::vector<positionPoint> doneBoxes, int stepCount);
    bool IsLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks);
    void RenderLevel(std::vector<std::vector<char>> levelMap, int stepCount);
    void RenderDebugMenu(positionPoint& pos);
};
    