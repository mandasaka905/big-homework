#include <graphics.h>
#include "GameConfig.h"
#include "GameManager.h"

int main()
{
    initgraph(GameConfig::W_WIDTH, GameConfig::W_HEIGHT);
    GameManager game;
    game.GameMainLoop();
    closegraph();
    return 0;
}