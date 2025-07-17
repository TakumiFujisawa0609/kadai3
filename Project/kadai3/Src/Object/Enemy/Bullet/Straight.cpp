#include "Straight.h"

Straight::Straight(void)
{
}

Straight::~Straight(void)
{
}

void Straight::SetParam(void)
{

    // ’e‚Ì‘å‚«‚³‚ğİ’è
    scale_ = { 0.4f, 0.4f, 0.4f };

    // ’e‚Ì‘¬“x
    speed_ = 8.0f;

    // ’e‚Ì¶‘¶”»’è
    isAlive_ = true;

    // ’e‚Ì¶‘¶ŠúŠÔ
    cntAlive_ = 300;

    // ’e‚Ì”¼Œa
    collisionRadius_ = 30.0f;

}
