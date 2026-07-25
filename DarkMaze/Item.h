#pragma once
#include "Entity.h"
class Key : public Entity
{
public:
    Key(int x, int y);
    virtual void Draw(int offX, int offY) override;
};
class BloodItem : public Entity
{
public:
    BloodItem(int x, int y);
    virtual void Draw(int offX, int offY) override;
};