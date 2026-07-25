#define _CRT_SECURE_NO_WARNINGS
#include "GameManager.h"
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <cmath>

GameManager::GameManager()
    : p1(140, 1), p2(660, -1)
{
    scoreL = 0;
    scoreR = 0;
    setL = 0;
    setR = 0;
    gameOver = false;
    gameStart = false;
    isPause = false;
    isAIMode = false;
}

void GameManager::DrawTextUI(char* str, int y, int fontSize, COLORREF textColor)
{
    wchar_t wBuf[256];
    mbstowcs(wBuf, str, 256);
    settextstyle(fontSize, 0, L"Arial");
    settextcolor(textColor);
    int strW = textwidth(wBuf);
    int drawX = static_cast<int>((GameConfig::W_WIDTH - strW) / 2.0);
    outtextxy(drawX, y, wBuf);
}

void GameManager::DrawGradientSky()
{
    for (int y = 0; y < GameConfig::SKY_END_Y; y++)
    {
        int blue = 235 - y / 3;
        int green = 206 - y / 4;
        setlinecolor(RGB(135, green, blue));
        line(0, y, GameConfig::W_WIDTH, y);
    }
    DrawCloud(100, 70, GameConfig::CLOUD_SIZES[0]);
    DrawCloud(360, 55, GameConfig::CLOUD_SIZES[1]);
    DrawCloud(620, 85, GameConfig::CLOUD_SIZES[2]);
    DrawTree(80, 60);
    DrawTree(720, 50);
}

void GameManager::DrawCloud(int x, int y, int size)
{
    setfillcolor(RGB(255, 255, 255));
    fillcircle(x, y, size);
    fillcircle(x + size, y, static_cast<int>(size * 0.82));
    fillcircle(x - size, y, static_cast<int>(size * 0.65));
    fillcircle(x + size / 2, y - size / 2, static_cast<int>(size * 0.7));
    fillcircle(x - size / 2, y - size / 3, static_cast<int>(size * 0.55));
}

void GameManager::DrawTree(int x, int height)
{
    setfillcolor(RGB(90, 50, 20));
    fillrectangle(x - 6, GameConfig::TREE_Y, x + 6, GameConfig::GRASS_TOP_Y);
    setfillcolor(RGB(20, 110, 20));
    fillcircle(x, GameConfig::TREE_Y - static_cast<int>(height / 2.0), height);
}

void GameManager::DrawDetailGrass()
{
    setfillcolor(RGB(26, 122, 26));
    fillrectangle(0, GameConfig::GRASS_TOP_Y, GameConfig::W_WIDTH, GameConfig::W_HEIGHT);
    setfillcolor(RGB(40, 145, 40));
    for (int i = 0; i < GameConfig::W_WIDTH; i += 28)
    {
        fillrectangle(i, GameConfig::GRASS_TOP_Y, i + 14, GameConfig::W_HEIGHT);
    }
    setlinestyle(PS_SOLID, 2);
    setlinecolor(RGB(15, 90, 15));
    for (int i = 0; i < GameConfig::W_WIDTH; i += 36)
    {
        line(i, GameConfig::GRASS_TOP_Y, i + 18, GameConfig::GRASS_TOP_Y + 16);
        line(i + 12, GameConfig::GRASS_TOP_Y, i - 6, GameConfig::GRASS_TOP_Y + 12);
    }
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 3);
    line(0, GameConfig::GRASS_TOP_Y, GameConfig::W_WIDTH, GameConfig::GRASS_TOP_Y);
}

void GameManager::DrawNet()
{
    int netLeftX = GameConfig::NET_CENTER_X - GameConfig::NET_POST_WIDTH / 2;
    int netRightX = GameConfig::NET_CENTER_X + GameConfig::NET_POST_WIDTH / 2;
    int netBottomY = GameConfig::GRASS_TOP_Y;
    int netTopY = netBottomY - GameConfig::NET_HEIGHT;

    setfillcolor(BROWN);
    setlinecolor(BROWN);

    fillrectangle(netLeftX, netTopY, netLeftX + GameConfig::NET_POST_WIDTH, netBottomY);
    fillrectangle(netRightX, netTopY, netRightX + GameConfig::NET_POST_WIDTH, netBottomY);

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 2);
    int lineStep = GameConfig::NET_HEIGHT / GameConfig::NET_LINE_COUNT;
    for (int i = 0; i <= GameConfig::NET_LINE_COUNT; i++)
    {
        int y = netTopY + i * lineStep;
        line(netLeftX + GameConfig::NET_POST_WIDTH, y, netRightX, y);
    }
}

void GameManager::DrawStartMenu()
{
    cleardevice();
    setbkmode(TRANSPARENT);

    DrawGradientSky();
    DrawDetailGrass();

    // 中间单根球网
    setfillcolor(BROWN);
    fillrectangle(GameConfig::NET_CENTER_X - 5, GameConfig::GRASS_TOP_Y - 150,
        GameConfig::NET_CENTER_X + 5, GameConfig::GRASS_TOP_Y);

    DrawCloud(100, 70, GameConfig::CLOUD_SIZES[0]);
    DrawCloud(360, 55, GameConfig::CLOUD_SIZES[1]);
    DrawCloud(620, 85, GameConfig::CLOUD_SIZES[2]);
    DrawTree(80, 60);
    DrawTree(GameConfig::W_WIDTH - 80, 60);

    // ========== 左上标题 ==========
    settextstyle(50, 35, _T("华文行楷"));
    settextcolor(BLACK);
    TCHAR title1[] = _T("火柴人羽");
    TCHAR title2[] = _T("毛球对决");
    outtextxy(52, 32, title1);
    outtextxy(68, 70, title2);

    // 标题旁小羽毛球
    setfillcolor(WHITE);
    setlinecolor(BLACK);
    // 左侧羽毛球
    fillcircle(36, 40, 6);
    circle(36, 40, 6);
    line(36, 47, 33, 55);
    line(36, 47, 39, 55);
    line(36, 47, 36, 57);
    // 标题中间羽毛球
    fillcircle(305, 50, 5);
    circle(305, 50, 5);
    line(305, 56, 302, 64);
    line(305, 56, 308, 64);
    line(305, 56, 305, 66);
    // 球网上方羽毛球
    fillcircle(GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 170, 7);
    circle(GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 170, 7);
    line(GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 163, GameConfig::NET_CENTER_X - 3, GameConfig::GRASS_TOP_Y - 155);
    line(GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 163, GameConfig::NET_CENTER_X + 3, GameConfig::GRASS_TOP_Y - 155);
    line(GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 163, GameConfig::NET_CENTER_X, GameConfig::GRASS_TOP_Y - 153);

    // ========== 右侧规则面板 ==========
    int ruleBoxX = GameConfig::W_WIDTH - 290;
    int ruleBoxY = 80;
    int ruleW = 250;
    int ruleH = 230;
    setfillcolor(WHITE);
    fillroundrect(ruleBoxX, ruleBoxY, ruleBoxX + ruleW, ruleBoxY + ruleH, 12, 12);
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID, 2);
    roundrect(ruleBoxX, ruleBoxY, ruleBoxX + ruleW, ruleBoxY + ruleH, 12, 12);

    settextstyle(28, 0, _T("黑体"));
    TCHAR ruleHead[] = _T("游戏规则");
    int headW = textwidth(ruleHead);
    outtextxy(ruleBoxX + (ruleW - headW) / 2, ruleBoxY + 10, ruleHead);

    settextstyle(21, 0, _T("微软雅黑"));
    TCHAR r1[] = _T("1. 先达到5分获胜");
    TCHAR r2[] = _T("2. 点击鼠标发球");
    TCHAR r3[] = _T("3. A/D 或 ←→ 移动");
    TCHAR r4[] = _T("4. W/↑普通跳，空格高跳");
    TCHAR r5[] = _T("5. S/Enter 击球");
    outtextxy(ruleBoxX + 18, ruleBoxY + 50, r1);
    outtextxy(ruleBoxX + 18, ruleBoxY + 80, r2);
    outtextxy(ruleBoxX + 18, ruleBoxY + 110, r3);
    outtextxy(ruleBoxX + 18, ruleBoxY + 140, r4);
    outtextxy(ruleBoxX + 18, ruleBoxY + 170, r5);

    // ========== 底部开始按钮 ==========
    int btnW = 300;
    int btnH = 80;
    int btnX = (GameConfig::W_WIDTH - btnW) / 2;
    int btnY = GameConfig::GRASS_TOP_Y - 100;
    setfillcolor(WHITE);
    fillroundrect(btnX, btnY, btnX + btnW, btnY + btnH, 20, 20);
    setlinecolor(BLACK);
    roundrect(btnX, btnY, btnX + btnW, btnY + btnH, 20, 20);

    settextstyle(38, 0, _T("黑体"));
    TCHAR btnText[] = _T("开始游戏");
    int btnTextW = textwidth(btnText);
    outtextxy(btnX + (btnW - btnTextW) / 2, btnY + 22, btnText);

    FlushBatchDraw();
}

void GameManager::DrawPauseUI()
{
    setfillcolor(COLORREF(RGB(0, 0, 0)) | (130 << 24));
    fillrectangle(0, 0, GameConfig::W_WIDTH, GameConfig::W_HEIGHT);

    char pauseText[] = "GAME PAUSED";
    DrawTextUI(pauseText, 160, GameConfig::FONT_PAUSE, WHITE);

    char resumeTip[] = "Press ESC to continue";
    DrawTextUI(resumeTip, 240, GameConfig::FONT_TIP + 8, WHITE);

    char quitTip[] = "Press Q to exit match";
    DrawTextUI(quitTip, 280, GameConfig::FONT_TIP, WHITE);
}

void GameManager::DrawGameScene()
{
    for (int y = 0; y < GameConfig::SKY_END_Y; y++)
    {
        int blue = 235 - y / 3;
        int green = 206 - y / 4;
        setlinecolor(RGB(135, green, blue));
        line(0, y, GameConfig::W_WIDTH, y);
    }
    DrawCloud(100, 70, GameConfig::CLOUD_SIZES[0]);
    DrawCloud(360, 55, GameConfig::CLOUD_SIZES[1]);
    DrawCloud(620, 85, GameConfig::CLOUD_SIZES[2]);
    DrawTree(80, 60);
    DrawTree(GameConfig::W_WIDTH - 80, 60);

    DrawGradientSky();
    DrawDetailGrass();
    DrawNet();

    char scoreText[40];
    sprintf_s(scoreText, "%d  :  %d", scoreL, scoreR);
    DrawTextUI(scoreText, 10, GameConfig::FONT_SCORE, WHITE);

    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(22, 0, _T("微软雅黑"));
    TCHAR bottomTip[] = _T("玩家1：W跳跃 空格高跳 A/D左右移动 S挥拍击球        玩家2：↑跳跃 7高跳 ←→移动 ↓挥拍击球");
    int tipW = textwidth(bottomTip);
    outtextxy((GameConfig::W_WIDTH - tipW) / 2, GameConfig::W_HEIGHT - 30, bottomTip);
}

void GameManager::ScoreJudge()
{
    if (!ball.IsOutGround())
        return;
    if (ball.GetFloatX() < GameConfig::NET_CENTER_X)
        scoreR++;
    else
        scoreL++;
    if (scoreL >= GameConfig::WIN_SCORE || scoreR >= GameConfig::WIN_SCORE)
    {
        if (scoreL >= GameConfig::SET_WIN) setL++;
        else setR++;
        if (setL >= GameConfig::SET_WIN || setR >= GameConfig::SET_WIN)
            gameOver = true;
        else
        {
            scoreL = 0;
            scoreR = 0;
        }
    }
    ball.ResetServe(scoreL <= scoreR);
}

void GameManager::DrawWinScreen()
{
    cleardevice();
    DrawGradientSky();
    DrawDetailGrass();
    DrawNet();

    char winMsg[50];
    if (setL >= GameConfig::SET_WIN)
        sprintf_s(winMsg, "Left Player Wins The Match!");
    else
        sprintf_s(winMsg, "Right Player Wins The Match!");
    DrawTextUI(winMsg, 190, GameConfig::FONT_WIN, YELLOW);

    char closeTip[] = "Press any key to close game";
    DrawTextUI(closeTip, 290, GameConfig::FONT_TIP + 8, WHITE);

    int ret = _getch();
    (void)ret;
}

void GameManager::GameMainLoop()
{
    DrawStartMenu();

    int startKey = _getch();
    if (startKey == '2') isAIMode = true;
    gameStart = true;
    BeginBatchDraw();
    int keyInput = 0;
    while (!gameOver)
    {
        cleardevice();
        if (_kbhit())
        {
            keyInput = _getch();
            if (keyInput == 27)
            {
                isPause = !isPause;
                if (isPause)
                {
                    DrawGameScene();
                    DrawPauseUI();
                    FlushBatchDraw();
                    while (true)
                    {
                        int pauseKey = _getch();
                        if (pauseKey == 27)
                        {
                            isPause = false;
                            break;
                        }
                        if (pauseKey == 'q' || pauseKey == 'Q')
                        {
                            gameOver = true;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            keyInput = 0;
        }

        p1.InputProcess(keyInput, true);
        if (isAIMode)
            p2.AIProcess(ball);
        else
            p2.InputProcess(keyInput, false);

        p1.UpdateStatus();
        p2.UpdateStatus();
        ball.UpdatePhysics();

        bool smash1 = false, smash2 = false;
        float bx = ball.GetFloatX();
        float by = ball.GetFloatY();
        if (keyInput == 's' && p1.CheckRacketHit(static_cast<int>(bx), static_cast<int>(by), smash1))
        {
            if (smash1) ball.HitSmash(p1.GetDir());
            else ball.HitNormal(p1.GetDir());
        }
        if (!isAIMode && keyInput == 80 && p2.CheckRacketHit(static_cast<int>(bx), static_cast<int>(by), smash2))
        {
            if (smash2) ball.HitSmash(p2.GetDir());
            else ball.HitNormal(p2.GetDir());
        }

        DrawGameScene();
        p1.DrawFullStick();
        p2.DrawFullStick();
        ball.DrawShuttle();
        ScoreJudge();

        Sleep(GameConfig::FRAME_DELAY);
        FlushBatchDraw();
    }
    EndBatchDraw();
    DrawWinScreen();
}