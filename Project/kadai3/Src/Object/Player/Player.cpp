#include "Player.h"
#include "../../Utility/AsoUtility.h"
#include "../../Input/InputManager.h"
#include "../../Camera/Camera.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(void)
{
	// ���f���̑傫��
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	// ���f���̊p�x
	angle_ = { 0.0f, 0.0f , 0.0f };
	MV1SetRotationXYZ(modelId_, angle_);

	// ���f���̍��W
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	// ���f���̐F����(���Ȕ���)
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	// �W�����v�͂̏�����
	jumpPow_ = 0.0f;

	// �A�j���[�V����
	prevAnimType_ = ANIM_TYPE::IDEL;
	nowAnimType_ = ANIM_TYPE::IDEL;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;
}

void Player::Load(void)
{
	// ���f���̃��[�h
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	// ������
	Init();

	// �A�j���[�V����������(�ǂݍ��݌�)
	// Walk�A�j���[�V�������A�^�b�`����
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	// �A�j���[�V�����̑��Đ����Ԃ��擾
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);
}

void Player::Update(void)
{
	// �ړ�����
	ProcessMove();

	// �W�����v����
	ProcessJump();

	// �A�j���[�V�����̍X�V
	UpdateAnim();

	// �J�����Ɏ��g�̍��W��n��
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{
	// ���f���̕`��
	MV1DrawModel(modelId_);
}

void Player::Release(void)
{
	// ���f���̍폜
	MV1DeleteModel(modelId_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

void Player::CollisionStage(VECTOR pos)
{
	// �Փ˂����ʒu
	pos_ = pos;
	jumpPow_ = 0.0f;
}

void Player::ProcessMove(void)
{
	// �ړ����������߂�
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	// ��ړ�
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	// ���ړ�
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	// ���ړ�
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}
	// �E�ړ�
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}

	// �ړ����Ă�����
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		// ���f���̈ړ�������Y����]������
		// �������p�x(���W�A��)�ɕϊ�����
		angle_.y = atan2(moveDir.x, moveDir.z);

		// ���f����Z�̃}�C�i�X�����������Ă���̂ŉ�]������
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		// ���f���ɉ�]��ݒ肷��
		MV1SetRotationXYZ(modelId_, angle_);

		// �ړ��ʂ��v�Z����(�����~�X�s�[�h)
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		// �ړ�����(���W�{�ړ���)
		pos_ = VAdd(pos_, movePow);

		// ���f���ɍ��W��ݒ肷��
		MV1SetPosition(modelId_, pos_);

		// �A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	// �ړ����Ă��Ȃ�
	else
	{
		// �A�j���[�V������ύX����
		nowAnimType_ = ANIM_TYPE::IDEL;
	}
}

void Player::ProcessJump(void)
{
	// �d��
	jumpPow_ -= GRAVITY;

	// �v���C���[�̍��W�ɃW�����v�͂����Z����
	pos_.y += jumpPow_;

	// �Փ˔���O�̗�������
	if (pos_.y < -1000.0f)
	{
		// ������
		Init();
	}

	// ���f���ɍ��W��ݒ肷��
	MV1SetPosition(modelId_, pos_);
}

void Player::UpdateAnim(void)
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
