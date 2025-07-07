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
	// モデルの大きさ
	scale_ = SCALE;
	MV1SetScale(modelId_, scale_);

	// モデルの座標
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	// モデルの色調整(自己発光)
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);
}

void Player::Load(void)
{
	// モデルのロード
	modelId_ = MV1LoadModel("Data/Model/Player/Player.mv1");
}

void Player::LoadEnd(void)
{
	// 初期化
	Init();
}

void Player::Update(void)
{
	// 移動操作
	ProcessMove();
}

void Player::Draw(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::Release(void)
{
	// モデルの削除
	MV1DeleteModel(modelId_);
}

void Player::ProcessMove(void)
{
	// 移動方向を決める
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;

	// 上移動
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_W))
	{
		moveDir = AsoUtility::DIR_F;
	}
	// 下移動
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_S))
	{
		moveDir = AsoUtility::DIR_B;
	}
	// 左移動
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_A))
	{
		moveDir = AsoUtility::DIR_L;
	}
	// 右移動
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_D))
	{
		moveDir = AsoUtility::DIR_R;
	}

	// 移動していたら
	if (!AsoUtility::EqualsVZero(moveDir))
	{
		// 移動量を計算する(方向×スピード)
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		// 移動処理(座標＋移動量)
		pos_ = VAdd(pos_, movePow);

		// モデルに座標を設定する
		MV1SetPosition(modelId_, pos_);
	}
}
