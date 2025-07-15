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

	// �����t���O�͐؂��Ă���
	isAlive_ = false;

	// �A�j���[�V����
	prevAnimType_ = ANIM_TYPE::WALK;
	nowAnimType_ = ANIM_TYPE::WALK;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;

	// �p�����[�^�̐ݒ�
	SetParam();

	// ���Ȕ���
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	// �傫���ύX
	MV1SetScale(modelId_, scale_);

	// �o�����W�̐ݒ�
	SetSpawnPosition();

	// �v���C���[�̕���������
	LookPlayer();
}

void EnemyBase::Load(TYPE type, int originModelId)
{
	// �G�l�~�[���
	type_ = type;

	// ���f���̕���
	modelId_ = MV1DuplicateModel(originModelId);
}

void EnemyBase::LoadEnd(void)
{
	// �A�j���[�V����������(�ǂݍ��݌�)
	// Walk�A�j���[�V�������A�^�b�`����
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	// �A�j���[�V�����̑��Đ����Ԃ��擾
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);
}

void EnemyBase::Update(void)
{
	// �������Ă��Ȃ��Ȃ珈�����Ȃ�
	if (!isAlive_)
		return;

	// �v���C���[�̕���������
	LookPlayer();

	// �ړ�
	Move();

	// �A�j���[�V�����X�V
	UpdateAnim();
}

void EnemyBase::Draw(void)
{
	// �������Ă��Ȃ��Ȃ珈�����Ȃ�
	if (!isAlive_)
		return;

	// �`��
	MV1DrawModel(modelId_);
}

void EnemyBase::Release(void)
{
	// ���f���̍폜
	MV1DeleteModel(modelId_);
}

void EnemyBase::SetIsAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

bool EnemyBase::GetIsAlive(void)
{
	return isAlive_;
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

	// �G�̈ړ�����
	if (pos_.x < 0.0f)
	{
		pos_.x = 0.0f;
	}
	if (pos_.x > Stage::STAGE_SIZE_X)
	{
		pos_.x = Stage::STAGE_SIZE_X;
	}
	if (pos_.z < 0.0f)
	{
		pos_.z = 0.0f;
	}
	if (pos_.z > Stage::STAGE_SIZE_Z)
	{
		pos_.z = Stage::STAGE_SIZE_Z;
	}

	// ���f���̍��W�𔽉f������
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::UpdateAnim(void)
{
	// �A�j���[�V�������ύX���ꂽ�H
	if (prevAnimType_ != nowAnimType_)
	{
		// �A�j���[�V������ʂ����킹��
		prevAnimType_ = nowAnimType_;

		// ���f������O��̃A�j���[�V�������O��
		MV1DetachAnim(modelId_, attachNo_);

		// �V�����A�j���[�V�����ɕύX����
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		// �A�j���[�V���������Ԃ̎擾
		totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

		// �A�j���[�V�������Ԃ�������
		nowAnimTime_ = 0.0f;
	}

	// �A�j���[�V������i�߂�
	nowAnimTime_ += 1.0f;

	// �A�j���[�V���������[�v
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	// �A�j���[�V�����ݒ�
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}

void EnemyBase::SetSpawnPosition(void)
{
	// �X�e�[�W�̔��a
	float radius = Stage::STAGE_SIZE_X * 0.5f;

	// �X�e�[�W�̒��S���W
	VECTOR centerPos = VGet(radius, 0.0f, radius);

	// �����_���Ȋp�x���擾����(360�x)
	int degree = GetRand(360);
	float radian = static_cast<float>(degree) * DX_PI_F / 180.0f;

	// �p�x������������߂�
	float dirX = sinf(radian);
	float dirZ = cosf(radian);

	// �����_���ȕ����𔼌a���L�΂����x�N�g��
	VECTOR vec = VScale(VGet(dirX, 0.0f, dirZ), radius);

	// ���S�_�̍��W�ɉ��Z���āA�����_���ȍ��W�����߂�
	VECTOR pos = VAdd(centerPos, vec);

	// �o�����W
	pos_ = pos;
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::SetParam(void)
{
}
