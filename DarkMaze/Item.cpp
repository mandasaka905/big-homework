#include "Item.h"
#include <graphics.h>
Key::Key(int x, int y) : Entity(x, y) {}
void Key::Draw(int offX, int offY)
{
    int cx = GetPos().x * cellSize + cellSize / 2 + offX;
    int cy = GetPos().y * cellSize + cellSize / 2 + offY;
    setfillcolor(YELLOW);
    fillcircle(cx - 6, cy, 5);
    bar(cx - 2, cy - 2, cx + 10, cy + 2);
    bar(cx + 6, cy + 2, cx + 10, cy + 6);
    bar(cx + 2, cy + 2, cx + 6, cy + 6);
}
BloodItem::BloodItem(int x, int y) : Entity(x, y) {}
void BloodItem::Draw(int offX, int offY)
{
    int cx = GetPos().x * cellSize + cellSize / 2 + offX;
    int cy = GetPos().y * cellSize + cellSize / 2 + offY;
    setfillcolor(RED);
    bar(cx - 8, cy - 3, cx + 8, cy + 3);
    bar(cx - 3, cy - 8, cx + 3, cy + 8);
}