#include "Shuttlecock.h"
#include <graphics.h>
#include <cmath>
#include <algorithm>

const float GameConfig::BALL_GRAVITY = 0.32f;
const float GameConfig::AIR_RESISTANCE = 0.99f;
const float GameConfig::WIND_FORCE = 0.02f;
const float GameConfig::LOB_POWER = 6.2f;
const float GameConfig::SMASH_POWER = 15.5f;
const float GameConfig::BOUNCE_RATE = 0.65f;
const int GameConfig::CLOUD_SIZES[3] = { 32, 42, 36 };

Shuttlecock::Shuttlecock()
{
    ResetServe(true);
}

void Shuttlecock::ResetServe(bool leftServe)
{
    trailList.clear();
    if (leftServe)
    {
        x = GameConfig::NET_CENTER_X - 80;
        vx = 3.5f;
        serveSide = 0;
    }
    else
    {
        x = GameConfig::NET_CENTER_X + 80;
        vx = -3.5f;
        serveSide = 1;
    }
    y = 110.f;
    vy = -4.f;
}

void Shuttlecock::UpdatePhysics()
{
    // 空气阻力+微风系统
    vx *= GameConfig::AIR_RESISTANCE;
    vx += GameConfig::WIND_FORCE;
    vy += GameConfig::BALL_GRAVITY;
    x += vx;
    y += vy;

    // 生成渐变残影
    trailList.push_back({ x, y, 255 });
    if (trailList.size() > GameConfig::TRAIL_MAX)
        trailList.erase(trailList.begin());
    for (int i = 0; i < trailList.size(); i++)
        trailList[i].alpha = 255 - i * 22;

    // 左右墙壁碰撞反弹
    if (x < GameConfig::BALL_LEFT_BOUND)
    {
        x = GameConfig::BALL_LEFT_BOUND;
        vx *= -GameConfig::BOUNCE_RATE;
    }
    if (x > GameConfig::BALL_RIGHT_BOUND)
    {
        x = GameConfig::BALL_RIGHT_BOUND;
        vx *= -GameConfig::BOUNCE_RATE;
    }
    // 球网碰撞判定
    if (IsNetCollision())
    {
        vx *= -0.72f;
        x = GameConfig::NET_CENTER_X + (x > GameConfig::NET_CENTER_X ? 22.f : -22.f);
    }
}

bool Shuttlecock::IsNetCollision()
{
    return fabs(x - GameConfig::NET_CENTER_X) < 18 && y > GameConfig::GRASS_TOP_Y - GameConfig::NET_HEIGHT;
}

void Shuttlecock::HitNormal(int faceDir)
{
    vy = -11.8f;
    vx = faceDir * GameConfig::LOB_POWER;
}

void Shuttlecock::HitSmash(int faceDir)
{
    vy = GameConfig::SMASH_POWER;
    vx = faceDir * (GameConfig::LOB_POWER * 1.7f);
}

bool Shuttlecock::IsOutGround()
{
    return y >= GameConfig::GRASS_TOP_Y;
}

void Shuttlecock::DrawShuttle()
{
    // 金色渐变拖尾
    int i = 0;
    for (auto& node : trailList)
    {
        int r = 255;
        int g = 225 - (int)(i * 2.2);
        int b = 0;
        setfillcolor(RGB(r, g, b));
        fillcircle((int)node.x, (int)node.y, 3);
        i++;
    }
    // 羽毛球主体
    setfillcolor(RGB(255, 205, 0));
    fillcircle((int)x, (int)y, 10);

    setfillcolor(RGB(255, 255, 255));
    fillcircle((int)x, (int)y + 9, 5);

}

int Shuttlecock::GetPosX()
{
    return (int)x;
}
int Shuttlecock::GetPosY()
{
    return (int)y;
}
float Shuttlecock::GetFloatX()
{
    return x;
}
float Shuttlecock::GetFloatY()
{
    return y;
}
float Shuttlecock::GetVelX()
{
    return vx;
}
float Shuttlecock::GetVelY()
{
    return vy;
}