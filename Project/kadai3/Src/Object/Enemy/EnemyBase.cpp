#include "EnemyBase.h"
#include "../../Utility/AsoUtility.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"

EnemyBase::EnemyBase(void)
{
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(Player* player)
{
	// �v���C���[�̃|�C���g���擾
	player_ = player;

	// �ړ����x�̏�����
	speed_ = 5.0f;

	// �v���C���[�̕���������
	LookPlayer();
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
	// �v���C���[�̕���������
	LookPlayer();

	// �ړ�
	Move();
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

void EnemyBase::LookPlayer(void)
{
	// �v���C���[�̌������v�Z
	VECTOR diff = VSub(player_->GetPos(), pos_);
	diff.y = 0.0f;
	// �x�N�g���𐳋K��(�����݂̂̏��ɕϊ�)
	moveDir_ = VNorm(diff);

	// �������p�x�ɕϊ�(x��z���͉񂳂Ȃ�)
	angle_.x = 0.0f;
	angle_.z = 0.0f;
	angle_.y = atan2f(moveDir_.x, moveDir_.z);
	
	// ���f�����t���ʂ������Ă���̂�Y���𔽓]������
	angle_.y += AsoUtility::Deg2RadF(180.0f);

	// ���f���̉�]�𔽉f������
	MV1SetRotationXYZ(modelId_, angle_);
}

void EnemyBase::Move(void)
{
	// �ړ�����
	pos_ = VAdd(pos_, VScale(moveDir_, speed_));

	// ���f���̍��W�𔽉f������
	MV1SetPosition(modelId_, pos_);
}
