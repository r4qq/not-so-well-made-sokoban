#include "Level.hpp"
#include <vector>

class Game
{
    std::vector<Level> LevelList;
public:
    Game(void);
    void InitalizeGame(void);
    void PlayGame(void);
    std::vector<Level> GetLevels(void);

private:
    void DrawBanner(void);
    void AddLevels(void);
    void DrawMenu(void);
    void PlayerMovement(int dPX, int dPY, positionPoint &pos, std::vector<std::vector<char>> &currentMap, int &stepCount);
    void GameLoop(positionPoint startPos, std::vector<std::vector<char>> levelMap, std::vector<positionPoint> doneBoxes, int stepCount);
    bool IsLeveDone(std::vector<std::vector<char>> levelMap, std::vector<positionPoint> docks);
    void RenderLevelDebug(std::vector<std::vector<char>> levelMap, int stepCount);
    void RenderDebugMenu(positionPoint &pos);
};
    