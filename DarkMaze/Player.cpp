#include "Player.h"
#include <graphics.h>
Player::Player(int x, int y) : Entity(x, y), hp(100) {}
int Player::GetHP() const { return hp; }
void Player::AddHP(int val)
{
    hp += val;
    if (hp > 100) hp = 100;
    if (hp < 0) hp = 0;
}
void Player::Draw(int offX, int offY)
{
    int cx = GetPos().x * cellSize + cellSize / 2 + offX;
    int cy = GetPos().y * cellSize + cellSize / 2 + offY;
    setfillcolor(GREEN);
    fillcircle(cx, cy, cellSize / 2 - 5);
    setfillcolor(WHITE);
    fillcircle(cx - 4, cy - 3, 2);
    fillcircle(cx + 4, cy - 3, 2);
}