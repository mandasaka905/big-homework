#pragma once
class GameConfig
{
public:
    // 窗口基础尺寸
    static const int W_WIDTH = 800;
    static const int W_HEIGHT = 500;
    // 场地分层坐标
    static const int SKY_END_Y = 420;
    static const int GRASS_TOP_Y = 420;
    // 远景装饰
    static const int TREE_Y = 370;
    // 球网参数
    static const int NET_CENTER_X = 400;
    static const int NET_HEIGHT = 180;
    static const int NET_POST_WIDTH = 8;
    static const int NET_LINE_COUNT = 8;
    // 角色移动、跳跃属性
    static const int PLAYER_SPEED = 5;
    static const int JUMP_POWER_NORMAL = -17;
    static const int JUMP_POWER_HIGH = -22;
    static const int GRAVITY = 1;
    static const int SWING_DURATION = 14;
    static const int SWING_COOLDOWN = 8;
    // 羽毛球物理浮点常量（仅声明，外部初始化）
    static const float BALL_GRAVITY;
    static const float AIR_RESISTANCE;
    static const float WIND_FORCE;
    static const float LOB_POWER;
    static const float SMASH_POWER;
    static const float BOUNCE_RATE;
    // 羽毛球残影上限
    static const int TRAIL_MAX = 12;
    // 对局胜负规则
    static const int WIN_SCORE = 7;
    static const int SET_WIN = 2;
    // 帧率控制
    static const int FPS = 60;
    static const int FRAME_DELAY = 1000 / FPS;
    // 云朵绘制参数
    static const int CLOUD_COUNT = 3;
    static const int CLOUD_SIZES[3];
    // UI文字尺寸
    static const int FONT_TITLE = 48;
    static const int FONT_SCORE = 36;
    static const int FONT_TIP = 18;
    static const int FONT_WIN = 52;
    static const int FONT_PAUSE = 60;
    // 边界限制
    static const int PLAYER_LEFT_BOUND = 35;
    static const int PLAYER_RIGHT_BOUND = W_WIDTH - 35;
    static const int BALL_LEFT_BOUND = 12;
    static const int BALL_RIGHT_BOUND = W_WIDTH - 12;
};