#include "Monster.h"
#include <list>
#include "MapObj.h"
#include <graphics.h>
Monster::Monster(int x, int y, int t) : Entity(x, y), dir(1), type(t) {}
void Monster::Draw(int offX, int offY)
{
    int cx = GetPos().x * cellSize + cellSize / 2 + offX;
    int cy = GetPos().y * cellSize + cellSize / 2 + offY;
    int r = cellSize / 2 - 6;
    if (type == 0)
    {
        setfillcolor(BLUE);
        fillcircle(cx, cy, r);
        setfillcolor(WHITE);
        fillcircle(cx - 5, cy - 4, 3);
        fillcircle(cx + 5, cy - 4, 3);
        setfillcolor(BLACK);
        fillcircle(cx - 5, cy - 4, 1);
        fillcircle(cx + 5, cy - 4, 1);
        setcolor(BLACK);
        line(cx - 6, cy + 5, cx + 6, cy + 5);
    }
    else
    {
        setfillcolor(RGB(255, 128, 0));
        fillcircle(cx, cy, r);
        setfillcolor(WHITE);
        fillcircle(cx - 5, cy - 4, 3);
        fillcircle(cx + 5, cy - 4, 3);
        setfillcolor(BLACK);
        fillcircle(cx - 5, cy - 4, 1);
        fillcircle(cx + 5, cy - 4, 1);
        setcolor(BLACK);
        line(cx - 6, cy + 5, cx + 6, cy + 5);
        line(cx - 8, cy - r, cx - 4, cy - r - 8);
        line(cx + 8, cy - r, cx + 4, cy - r - 8);
    }
}
void Monster::Patrol(const std::list<Wall>& walls)
{
    Point cur = GetPos();
    int nx = cur.x + dir;
    bool hitWall = false;
    for (const auto& w : walls)
    {
        Point wp = w.GetPos();
        if (wp.x == nx && wp.y == cur.y)
        {
            hitWall = true;
            break;
        }
    }
    if (nx <= 0 || nx >= 19) hitWall = true;
    if (hitWall) dir = -dir;
    Move(dir, 0);
}