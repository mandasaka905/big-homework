#pragma once
#include "Entity.h"
#include <list>
class Wall;
class Monster : public Entity
{
private:
    int dir;
    int type;
public:
    Monster(int x, int y, int t);
    virtual void Draw(int offX, int offY) override;
    void Patrol(const std::list<Wall>& walls);
    int GetType() const { return type; }
};