#include "Straight.h"

Straight::Straight(void)
{
}

Straight::~Straight(void)
{
}

void Straight::SetParam(void)
{

    // �e�̑傫����ݒ�
    scale_ = { 0.4f, 0.4f, 0.4f };

    // �e�̑��x
    speed_ = 8.0f;

    // �e�̐�������
    isAlive_ = true;

    // �e�̐�������
    cntAlive_ = 300;

    // �e�̔��a
    collisionRadius_ = 30.0f;

}
