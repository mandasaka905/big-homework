#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
    int hp;
public:
    Player(int x, int y);
    int GetHP() const;
    void AddHP(int val);
    virtual void Draw(int offX, int offY) override;
};