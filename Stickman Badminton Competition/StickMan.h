#pragma once
#include "GameConfig.h"

class Shuttlecock;

class StickMan
{
private:
    int posX, posY;
    int faceDir;
    int jumpVel;
    bool isJump;
    bool isHighJump;
    int swingFrame;
    bool isSwinging;
    int swingCooldown;
    int walkFrame;
    float legSwing;

    float vX;       // 横向速度浮点
    float groundY;  // 地面高度
public:
    StickMan(int spawnX, int dir);
    void InputProcess(int key, bool isPlayer1);
    void AIProcess(Shuttlecock& ball);
    void UpdateStatus();
    bool CheckRacketHit(int ballX, int ballY, bool& triggerSmash);
    void DrawFullStick();
    int GetDir();
    int GetX();
    int GetY();
};