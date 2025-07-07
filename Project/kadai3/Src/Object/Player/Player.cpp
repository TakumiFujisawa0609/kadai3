#include "Player.h"
#include "../../Utility/AsoUtility.h"
#include "../../Input/InputManager.h"

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

	// ���f���̍��W
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	// ���f���̐F����(���Ȕ���)
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);
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
}

void Player::Update(void)
{
	// �ړ�����
	ProcessMove();
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
		// �ړ��ʂ��v�Z����(�����~�X�s�[�h)
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		// �ړ�����(���W�{�ړ���)
		pos_ = VAdd(pos_, movePow);

		// ���f���ɍ��W��ݒ肷��
		MV1SetPosition(modelId_, pos_);
	}
}
