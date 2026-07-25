#pragma once
#include "GameConfig.h"
#include <vector>
struct TrailNode
{
    float x, y;
    int alpha;
};
class Shuttlecock
{
private:
    float x, y;
    float vx, vy;
    std::vector<TrailNode> trailList;
    int serveSide;
public:
    Shuttlecock();
    void ResetServe(bool leftServe);
    void UpdatePhysics();
    void HitNormal(int faceDir);
    void HitSmash(int faceDir);
    bool IsOutGround();
    bool IsNetCollision();
    void DrawShuttle();
    int GetPosX();
    int GetPosY();
    float GetFloatX();
    float GetFloatY();
    float GetVelX();
    float GetVelY();
};