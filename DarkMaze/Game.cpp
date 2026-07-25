#include "Game.h"
#include <graphics.h>
#include <conio.h>
#include <tchar.h>

const int TOTAL_KEY = 3;
const int NEED_KEY = 2;
const int offsetX = 240;
const int offsetY = 60;

Game::Game()
    : player(2, 2), exitObj(17, 12), gameWin(false), keyNeed(NEED_KEY), stepCount(0)
{
    startClock = clock();
    for (int i = 0; i < 20; i++)
    {
        wallList.emplace_back(i, 0);
        wallList.emplace_back(i, 14);
    }
    for (int i = 1; i < 14; i++)
    {
        wallList.emplace_back(0, i);
        wallList.emplace_back(19, i);
    }
    wallList.emplace_back(5, 3);
    wallList.emplace_back(6, 3);
    wallList.emplace_back(6, 4);

    keyList.emplace_back(10, 5);
    keyList.emplace_back(3, 8);
    keyList.emplace_back(14, 4);
    bloodList.emplace_back(7, 9);
    bloodList.emplace_back(12, 11);
    monsterList.emplace_back(4, 6, 0);
    monsterList.emplace_back(9, 10, 1);
}

void Game::ShowStartScreen()
{
    cleardevice();
    settextcolor(WHITE);
    settextstyle(36, 0, _T("宋体"));
    outtextxy(480, 80, _T("地牢逃脱"));

    settextstyle(22, 0, _T("宋体"));
    outtextxy(120, 160, _T("游戏规则："));
    outtextxy(140, 195, _T("● 绿色圆点：玩家"));
    outtextxy(140, 225, _T("● 黄色钥匙：收集钥匙才能通关"));
    outtextxy(140, 255, _T("● 红色十字：血包，恢复生命值"));
    outtextxy(140, 285, _T("● 蓝色怪兽：普通速度，碰到扣20血"));
    outtextxy(140, 315, _T("● 橙色怪兽：速度很快，碰到扣30血"));
    outtextxy(140, 345, _T("● 绿色出口：收集2把钥匙后可通关"));

    outtextxy(120, 400, _T("操作说明："));
    outtextxy(140, 430, _T("WASD 移动"));
    outtextxy(140, 455, _T("Q 退出游戏"));

    settextcolor(YELLOW);
    settextstyle(28, 0, _T("宋体"));
    outtextxy(420, 540, _T("按任意键开始游戏"));
    _getch();
}

void Game::UpdateMonster()
{
    for (auto& m : monsterList)
    {
        if (m.GetType() == 0)
        {
            m.Patrol(wallList);
        }
        else
        {
            m.Patrol(wallList);
            m.Patrol(wallList);
            m.Patrol(wallList);
        }
    }
}

void Game::HandleInput()
{
    if (_kbhit())
    {
        char ch = _getch();
        int dx = 0, dy = 0;
        if (ch == 'w' || ch == 'W') dy = -1;
        if (ch == 's' || ch == 'S') dy = 1;
        if (ch == 'a' || ch == 'A') dx = -1;
        if (ch == 'd' || ch == 'D') dx = 1;
        if (ch == 'q' || ch == 'Q') exit(0);

        if (dx != 0 || dy != 0)
        {
            Point curPos = player.GetPos();
            int targetX = curPos.x + dx;
            int targetY = curPos.y + dy;
            bool canMove = true;
            for (auto& wall : wallList)
            {
                Point wPos = wall.GetPos();
                if (wPos.x == targetX && wPos.y == targetY)
                {
                    canMove = false;
                    break;
                }
            }
            if (canMove)
            {
                player.Move(dx, dy);
                stepCount++;
                Point newPos = player.GetPos();
                for (auto iter = keyList.begin(); iter != keyList.end();)
                {
                    Point kPos = iter->GetPos();
                    if (newPos.x == kPos.x && newPos.y == kPos.y)
                        iter = keyList.erase(iter);
                    else ++iter;
                }
                for (auto iter = bloodList.begin(); iter != bloodList.end();)
                {
                    Point bPos = iter->GetPos();
                    if (newPos.x == bPos.x && newPos.y == bPos.y && player.GetHP() < 100)
                    {
                        player.AddHP(30);
                        iter = bloodList.erase(iter);
                    }
                    else ++iter;
                }
                for (auto& m : monsterList)
                {
                    Point mPos = m.GetPos();
                    if (newPos.x == mPos.x && newPos.y == mPos.y)
                    {
                        if (m.GetType() == 1) player.AddHP(-30);
                        else player.AddHP(-20);
                    }
                }
                int collected = TOTAL_KEY - static_cast<int>(keyList.size());
                Point exitPos = exitObj.GetPos();
                if (newPos.x == exitPos.x && newPos.y == exitPos.y)
                {
                    if (collected >= keyNeed) gameWin = true;
                }
            }
        }
    }
}

void Game::Render()
{
    cleardevice();
    Point playerPos = player.GetPos();
    for (auto& m : monsterList)
    {
        Point mPos = m.GetPos();
        if (playerPos.x == mPos.x && playerPos.y == mPos.y)
        {
            if (m.GetType() == 1) player.AddHP(-2);
            else player.AddHP(-1);
        }
    }

    // 绘制墙体
    for (auto& wall : wallList)
    {
        Point p = wall.GetPos();
        int x = p.x * CELL_SIZE + offsetX;
        int y = p.y * CELL_SIZE + offsetY;
        setcolor(WHITE);
        rectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);
    }
    // 怪物
    for (auto& m : monsterList)
    {
        m.Draw(offsetX, offsetY);
    }
    // 钥匙
    for (auto& k : keyList)
    {
        k.Draw(offsetX, offsetY);
    }
    // 血包
    if (player.GetHP() < 100)
    {
        for (auto& b : bloodList)
        {
            b.Draw(offsetX, offsetY);
        }
    }
    // 出口
    exitObj.Draw(offsetX, offsetY);
    // 玩家
    player.Draw(offsetX, offsetY);

    settextcolor(WHITE);
    settextstyle(22, 0, _T("宋体"));
    outtextxy(10, 680, _T("WASD移动 | Q退出"));

    int costSec = static_cast<int>((clock() - startClock) / CLOCKS_PER_SEC);
    TCHAR timeText[64], hpText[64], keyText[64], stepText[64];
    _stprintf_s(timeText, _T("用时：%d秒"), costSec);
    _stprintf_s(hpText, _T("血量：%d/100"), player.GetHP());
    int collectedKey = TOTAL_KEY - static_cast<int>(keyList.size());
    _stprintf_s(keyText, _T("钥匙：%d/%d"), collectedKey, keyNeed);
    _stprintf_s(stepText, _T("步数：%d"), stepCount);

    outtextxy(1020, 520, hpText);
    outtextxy(1020, 548, keyText);
    outtextxy(1020, 576, timeText);
    outtextxy(1020, 604, stepText);

    if (collectedKey >= keyNeed)
    {
        settextcolor(YELLOW);
        outtextxy(10, 620, _T("✅ 钥匙集齐，前往绿色出口通关！"));
        if (collectedKey >= TOTAL_KEY)
        {
            settextcolor(GREEN);
            outtextxy(10, 590, _T("🌸 收集全部钥匙，额外奖励达成！"));
        }
    }
    else
    {
        settextcolor(YELLOW);
        outtextxy(10, 620, _T("收集足够钥匙才能通关"));
    }

    int finalTime = static_cast<int>((clock() - startClock) / CLOCKS_PER_SEC);
    if (gameWin)
    {
        settextcolor(GREEN);
        settextstyle(28, 0, _T("宋体"));
        TCHAR winInfo[256];
        TCHAR star[32];
        if (stepCount <= 120)
            _stprintf_s(star, _T("⭐⭐⭐ 三星完美速通"));
        else if (stepCount <= 200)
            _stprintf_s(star, _T("⭐⭐ 二星标准通关"));
        else
            _stprintf_s(star, _T("⭐ 一星慢速通关"));
        _stprintf_s(winInfo, _T("🎉通关！用时%d秒，步数%d，收集钥匙%d\n%s"), finalTime, stepCount, collectedKey, star);
        outtextxy(400, 260, winInfo);
    }
    if (player.GetHP() <= 0)
    {
        settextcolor(RED);
        settextstyle(32, 0, _T("宋体"));
        outtextxy(520, 300, _T("💀血量耗尽，游戏失败"));
    }
}

bool Game::IsGameOver()
{
    return gameWin || player.GetHP() <= 0;
}