#include "Game.h"
#include <graphics.h>
#include <conio.h>
int main()
{
    initgraph(1280, 720);
    Game game;
    game.ShowStartScreen();
    while (true)
    {
        game.HandleInput();
        game.UpdateMonster();
        game.Render();
        FlushBatchDraw();
        Sleep(15);
        if (game.IsGameOver())
        {
            _getch();
            break;
        }
    }
    closegraph();
    return 0;
}