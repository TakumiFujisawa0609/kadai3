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
	// ���f���̃��[�h
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
	// �`��
	MV1DrawModel(modelId_);
}

void EnemyBase::Release(void)
{
	// ���f���̍폜
	MV1DeleteModel(modelId_);
}
