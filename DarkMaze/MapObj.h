#pragma once
#include "Entity.h"
class Wall : public Entity
{
public:
    Wall(int x, int y) : Entity(x, y) {}
    //  µœ÷¥ø–ÈDraw
    virtual void Draw(int offX, int offY) override;
};
class Exit : public Entity
{
public:
    Exit(int x, int y);
    virtual void Draw(int offX, int offY) override;
};