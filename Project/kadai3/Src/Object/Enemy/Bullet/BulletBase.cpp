#include "BulletBase.h"

BulletBase::BulletBase(void)
{
}

BulletBase::~BulletBase(void)
{
}

void BulletBase::Load(int originHandle)
{
    // モデルの複製
    modelId_ = MV1DuplicateModel(originHandle);
}

void BulletBase::LoadEnd(void)
{
}

void BulletBase::CreateBullet(VECTOR pos, VECTOR dir)
{
    // 弾の発射位置を設定
    pos_ = pos;

    // 弾の発射方向の設定
    dir_ = dir;

    // パラメータ設定
    SetParam();

    // 大きさの設定
    MV1SetScale(modelId_, scale_);

    // 位置の設定
    MV1SetPosition(modelId_, pos_);
}

void BulletBase::Update(void)
{

    if (!GetIsAlive())
    {
        // 生存していなければ処理中断
        return;
    }

    pos_ = VAdd(pos_, VScale(dir_, speed_));

    // 位置の設定
    MV1SetPosition(modelId_, pos_);

    // 生存カウンタの減少
    ReduceCntAlive();

}

void BulletBase::Draw()
{

    if (!GetIsAlive())
    {
        // 生存していなければ処理中断
        return;
    }

    // モデルの描画
    MV1DrawModel(modelId_);

    // デバッグ用当たり判定の描画
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
