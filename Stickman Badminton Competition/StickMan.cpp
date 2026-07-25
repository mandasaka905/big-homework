#include "StickMan.h"
#include "Shuttlecock.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <algorithm>

StickMan::StickMan(int spawnX, int dir)
{
    posX = spawnX;
    posY = GameConfig::GRASS_TOP_Y;
    faceDir = dir;
    jumpVel = 0;
    isJump = false;
    isHighJump = false;
    swingFrame = 0;
    isSwinging = false;
    swingCooldown = 0;
    walkFrame = 0;
    legSwing = 0.0f;
    vX = 0.0f;
    groundY = GameConfig::GRASS_TOP_Y;
}

void StickMan::InputProcess(int key, bool isPlayer1)
{
    if (isPlayer1)
    {
        if (key == 'a')
        {
            faceDir = -1;
            vX -= 0.9f;
            walkFrame++;
            legSwing += 0.35f;
        }
        if (key == 'd')
        {
            faceDir = 1;
            vX += 0.9f;
            walkFrame++;
            legSwing -= 0.35f;
        }
        if (key == 'w' && !isJump)
        {
            isJump = true;
            isHighJump = false;
            jumpVel = GameConfig::JUMP_POWER_NORMAL;
        }
        if (key == ' ' && !isJump)
        {
            isJump = true;
            isHighJump = true;
            jumpVel = GameConfig::JUMP_POWER_HIGH;
        }
        // 玩家1挥拍 S键
        if ((key == 's' || key == 'S') && swingCooldown <= 0 && !isSwinging)
        {
            isSwinging = true;
            swingFrame = GameConfig::SWING_DURATION;
            swingCooldown = GameConfig::SWING_COOLDOWN;
        }
    }
    else
    {
        if (key == 75)
        {
            faceDir = -1;
            vX -= 0.9f;
            walkFrame++;
            legSwing += 0.35f;
        }
        if (key == 77)
        {
            faceDir = 1;
            vX += 0.9f;
            walkFrame++;
            legSwing -= 0.35f;
        }
        if (key == 72 && !isJump)
        {
            isJump = true;
            isHighJump = false;
            jumpVel = GameConfig::JUMP_POWER_NORMAL;
        }
        if (key == 73 && !isJump)
        {
            isJump = true;
            isHighJump = true;
            jumpVel = GameConfig::JUMP_POWER_HIGH;
        }
        // 玩家2挥拍 ↓键
        if (key == 80 && swingCooldown <= 0 && !isSwinging)
        {
            isSwinging = true;
            swingFrame = GameConfig::SWING_DURATION;
            swingCooldown = GameConfig::SWING_COOLDOWN;
        }
    }
    posX = max(GameConfig::PLAYER_LEFT_BOUND, min(posX, GameConfig::PLAYER_RIGHT_BOUND));
}

void StickMan::AIProcess(Shuttlecock& ball)
{
    float ballX = ball.GetFloatX();
    float diff = ballX - posX;
    if (fabs(diff) > 60)
    {
        if (diff > 0)
            vX += (GameConfig::PLAYER_SPEED - 1) * 0.12f;
        else
            vX -= (GameConfig::PLAYER_SPEED - 1) * 0.12f;
        walkFrame++;
    }
    if (ball.GetFloatY() < GameConfig::GRASS_TOP_Y - 100 && !isJump)
    {
        isJump = true;
        jumpVel = GameConfig::JUMP_POWER_NORMAL;
    }
    bool smash = false;
    if (CheckRacketHit(ball.GetPosX(), ball.GetPosY(), smash) && swingCooldown <= 0)
    {
        isSwinging = true;
        swingFrame = GameConfig::SWING_DURATION;
        swingCooldown = GameConfig::SWING_COOLDOWN;
    }
}

void StickMan::UpdateStatus()
{
    vX *= 0.87f;
    if (vX > 6.0f) vX = 6.0f;
    if (vX < -6.0f) vX = -6.0f;
    posX += static_cast<int>(vX);

    posX = max(GameConfig::PLAYER_LEFT_BOUND, min(posX, GameConfig::W_WIDTH - 10));

    if (isJump)
    {
        if (jumpVel < 0)
            jumpVel += 4;
        else
            jumpVel += 7;

        posY += jumpVel;

        if (posY >= groundY)
        {
            posY = groundY;
            jumpVel = 0;
            isJump = false;
        }
    }

    // 挥拍计时递减，动画过渡
    if (isSwinging)
    {
        swingFrame--;
        if (swingFrame <= 0)
        {
            isSwinging = false;
        }
    }
    if (swingCooldown > 0) swingCooldown--;

    walkFrame++;
    legSwing = sin(walkFrame * 0.15f) * 3.5f;
}

bool StickMan::CheckRacketHit(int ballX, int ballY, bool& triggerSmash)
{
    int racketX = posX + faceDir * 50;
    int racketY = posY - 80;
    double dist = sqrt(pow(ballX - racketX, 2) + pow(ballY - racketY, 2));
    triggerSmash = isJump;
    return dist < 72 && isSwinging;
}

void StickMan::DrawFullStick()
{
    int x = posX;
    int y = posY;
    
    int lineW = 3;
    if (isSwinging || isJump)
        lineW = 5;
    setlinestyle(PS_SOLID, lineW);
    setlinecolor(BLACK);

    // ========== 1. 头部 + 动态五官 ==========
    int headRadius = 16;
    int headY = y - 90;
    circle(x, headY, headRadius);
    // 眼睛坐标偏移
    int eyeOffX = faceDir * 5;
    int eyeY = headY - 4;
    int eyeSize = 3;
    fillcircle(x - 6 + eyeOffX, eyeY, eyeSize);
    fillcircle(x + 6 + eyeOffX, eyeY, eyeSize);
    // 动态嘴巴
    if (isSwinging)
    {
        arc(x, headY + 6, x - 7, headY + 12, x + 7, headY + 12);
    }
    else if (isJump)
    {
        arc(x, headY + 8, x - 4, headY + 12, x + 4, headY + 12);
    }
    else
    {
        line(x - 5, headY + 8, x + 5, headY + 8);
    }

    // ========== 2. 躯干 ==========
    int bodyTop = headY + headRadius;
    int bodyBottom = y - 30;
    line(x, bodyTop, x, bodyBottom);

    // ========== 3. 腿部 ==========
    int legAnim = static_cast<int>(sin(legSwing) * 18);
    line(x, bodyBottom, x - 26 + legAnim, y);
    line(x, bodyBottom, x + 26 - legAnim, y);

    // ========== 4. 分状态绘制手臂 ==========
    int swingOff = (GameConfig::SWING_DURATION - swingFrame) * 4;
    int armBaseY = bodyBottom - 20;

    if (isSwinging)
    {
        // 挥拍状态
        int holdArmEndX = x + faceDir * (40 + swingOff);
        int holdArmEndY = armBaseY - swingOff / 3;
        // 持拍手
        line(x, armBaseY, holdArmEndX, holdArmEndY);
        // 球拍握在手掌末端
        int racketX = holdArmEndX + faceDir * 12;
        int racketY = holdArmEndY - 10;
        ellipse(racketX - 16, racketY - 16, racketX + 16, racketY + 16);
        // 后手向后摆平衡身体
        line(x, armBaseY, x - faceDir * 32, armBaseY + 15);
    }
    else if (isJump)
    {
        // 跳跃状态
        line(x, armBaseY, x - 28, armBaseY - 22);
        line(x, armBaseY, x + 28, armBaseY - 22);
        // 球拍挂在侧边
        int racketX = x + faceDir * 35;
        int racketY = armBaseY - 5;
        line(x, armBaseY, racketX, racketY);
        ellipse(racketX - 12, racketY - 12, racketX + 12, racketY + 12);
    }
    else
    {
        // 站立/行走状态
        float armSwing = sin(legSwing) * 12;
        // 持拍手自然垂在身前
        int holdArmX = x + faceDir * 22 + armSwing;
        int holdArmY = armBaseY + 10;
        line(x, armBaseY, holdArmX, holdArmY);
        // 球拍
        int racketX = holdArmX + faceDir * 8;
        int racketY = holdArmY - 6;
        line(holdArmX, holdArmY, racketX, racketY);
        ellipse(racketX - 10, racketY - 10, racketX + 10, racketY + 10);
        // 另一只手臂反向摆动
        int backArmX = x - faceDir * 22 - armSwing;
        int backArmY = armBaseY + 10;
        line(x, armBaseY, backArmX, backArmY);
    }
}

int StickMan::GetDir()
{
    return faceDir;
}
int StickMan::GetX()
{
    return posX;
}
int StickMan::GetY()
{
    return posY;
}