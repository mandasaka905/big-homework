#pragma once
#include <graphics.h>
#include "GameConfig.h"
#include "StickMan.h"
#include "Shuttlecock.h"

class GameManager
{
private:
    StickMan p1;
    StickMan p2;
    Shuttlecock ball;
    int scoreL, scoreR;
    int setL, setR;
    bool gameOver;
    bool gameStart;
    bool isPause;
    bool isAIMode;

    void DrawGradientSky();
    void DrawCloud(int x, int y, int size);
    void DrawTree(int x, int height);
    void DrawDetailGrass();
    void DrawNet();
    
    void DrawTextUI(char* str, int y, int fontSize, COLORREF textColor);
public:
    GameManager();
    void DrawStartMenu();
    void DrawGameScene();
    void DrawPauseUI();
    void ScoreJudge();
    void DrawWinScreen();
    void GameMainLoop();
};