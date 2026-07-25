#include "MapObj.h"
#include <graphics.h>

// Wall µœ÷Draw
void Wall::Draw(int offX, int offY)
{
    int x = GetPos().x * cellSize + offX;
    int y = GetPos().y * cellSize + offY;
    setcolor(WHITE);
    rectangle(x, y, x + cellSize, y + cellSize);
}

Exit::Exit(int x, int y) : Entity(x, y) {}
void Exit::Draw(int offX, int offY)
{
    int x = GetPos().x * cellSize + offX;
    int y = GetPos().y * cellSize + offY;
    setfillcolor(GREEN);
    fillrectangle(x + 4, y + 4, x + cellSize - 4, y + cellSize - 4);
}