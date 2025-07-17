#include "BulletBase.h"

BulletBase::BulletBase(void)
{
}

BulletBase::~BulletBase(void)
{
}

void BulletBase::Load(int originHandle)
{
    // ���f���̕���
    modelId_ = MV1DuplicateModel(originHandle);
}

void BulletBase::LoadEnd(void)
{
}

void BulletBase::CreateBullet(VECTOR pos, VECTOR dir)
{
    // �e�̔��ˈʒu��ݒ�
    pos_ = pos;

    // �e�̔��˕����̐ݒ�
    dir_ = dir;

    // �p�����[�^�ݒ�
    SetParam();

    // �傫���̐ݒ�
    MV1SetScale(modelId_, scale_);

    // �ʒu�̐ݒ�
    MV1SetPosition(modelId_, pos_);
}

void BulletBase::Update(void)
{

    if (!GetIsAlive())
    {
        // �������Ă��Ȃ���Ώ������f
        return;
    }

    pos_ = VAdd(pos_, VScale(dir_, speed_));

    // �ʒu�̐ݒ�
    MV1SetPosition(modelId_, pos_);

    // �����J�E���^�̌���
    ReduceCntAlive();

}

void BulletBase::Draw()
{

    if (!GetIsAlive())
    {
        // �������Ă��Ȃ���Ώ������f
        return;
    }

    // ���f���̕`��
    MV1DrawModel(modelId_);

    // �f�o�b�O�p�����蔻��̕`��
    DrawSphere3D(pos_, collisionRadius_, 10, 0xff0000, 0xff0000, false);

}

void BulletBase::Release(void)
{
    MV1DeleteModel(modelId_);
}

bool BulletBase::GetIsAlive(void)
{
    return isAlive_;
}

VECTOR BulletBase::GetPos(void)
{
    return pos_;
}

float BulletBase::GetCollisionRadius(void)
{
    return collisionRadius_;
}

void BulletBase::ReduceCntAlive(void)
{
    cntAlive_--;
    if (cntAlive_ < 0)
    {
        isAlive_ = false;
    }
}
