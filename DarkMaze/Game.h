#pragma once
#include <list>
#include "Entity.h"
#include "MapObj.h"
#include "Player.h"
#include "Item.h"
#include "Monster.h"
#include <ctime>

class Game
{
private:
    std::list<Wall> wallList;
    Player player;
    std::list<Key> keyList;
    std::list<BloodItem> bloodList;
    std::list<Monster> monsterList;
    Exit exitObj;
    bool gameWin;
    const int CELL_SIZE = 40;
    int keyNeed;
    clock_t startClock;
    int stepCount;
public:
    Game();
    void ShowStartScreen();
    void HandleInput();
    void Render();
    bool IsGameOver();
    void UpdateMonster();
};