#include "Player.h"

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
