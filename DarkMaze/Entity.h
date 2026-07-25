#pragma once
struct Point
{
    int x, y;
};
const int cellSize = 40;
class Entity
{
protected:
    Point pos;
public:
    Entity(int x, int y) : pos{ x, y } {}
    Point GetPos() const { return pos; }
    void Move(int dx, int dy) { pos.x += dx; pos.y += dy; }
    virtual void Draw(int offX, int offY) = 0;
};