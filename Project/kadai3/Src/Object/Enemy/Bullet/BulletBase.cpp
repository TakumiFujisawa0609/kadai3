#include "BulletBase.h"

BulletBase::BulletBase(void)
{
}

BulletBase::~BulletBase(void)
{
}

void BulletBase::Load(void)
{
    baseModelId_ = LoadGraph("");
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

    // 使用メモリ容量と読み込み時間の削減のため
    // モデルデータをいくつもメモリ上に存在させない
    modelId_ = MV1DuplicateModel(baseModelId_);

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

    // 弾を移動させる

    // 移動量の計算(方向×スピード)
    //VECTOR movePow;
    //movePow.x = dir_.x * speed_;
    //movePow.y = dir_.y * speed_;
    //movePow.z = dir_.z * speed_;

    // 移動処理
    //pos_.x += movePow.x;
    //pos_.y += movePow.y;
    //pos_.z += movePow.z;
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

BulletBase::TYPE BulletBase::GetType(void)
{
    return type_;
}

void BulletBase::ReduceCntAlive(void)
{
    cntAlive_--;
    if (cntAlive_ < 0)
    {
        isAlive_ = false;
    }
}
