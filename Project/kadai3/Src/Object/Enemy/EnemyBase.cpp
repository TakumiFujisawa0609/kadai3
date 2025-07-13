#include "EnemyBase.h"

EnemyBase::EnemyBase(void)
{
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(void)
{
}

void EnemyBase::Load(void)
{
	// モデルのロード
	modelId_ = MV1LoadModel("Data/Model/Enemy/Demon.mv1");
}

void EnemyBase::LoadEnd(void)
{
}

void EnemyBase::Update(void)
{
}

void EnemyBase::Draw(void)
{
	// 描画
	MV1DrawModel(modelId_);
}

void EnemyBase::Release(void)
{
	// モデルの削除
	MV1DeleteModel(modelId_);
}
