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

	// モデルの角度
	angle_ = { 0.0f, 0.0f , 0.0f };
	MV1SetRotationXYZ(modelId_, angle_);

	// モデルの座標
	pos_ = INIT_POS;
	MV1SetPosition(modelId_, pos_);

	// モデルの色調整(自己発光)
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	// アニメーション
	attachNo_ = 0;		
	nowAnimTime_ = 0.0f;	
	totalAnimTime_ = 0.0f;
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

	// アニメーション初期化(読み込み後)
	// Walkアニメーションをアタッチする
	attachNo_ = MV1AttachAnim(modelId_, 14);

	// アニメーションの総再生時間を取得
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);
}

void Player::Update(void)
{
	// 移動操作
	ProcessMove();

	// アニメーションの更新
	UpdateAnim();
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
		// モデルの移動方向にY軸回転させる
		// 方向を角度(ラジアン)に変換する
		angle_.y = atan2(moveDir.x, moveDir.z);

		// モデルがZのマイナス方向を向いているので回転させる
		angle_.y += AsoUtility::Deg2RadF(180.0f);

		// モデルに回転を設定する
		MV1SetRotationXYZ(modelId_, angle_);

		// 移動量を計算する(方向×スピード)
		VECTOR movePow = VScale(moveDir, MOVE_SPEED);

		// 移動処理(座標＋移動量)
		pos_ = VAdd(pos_, movePow);

		// モデルに座標を設定する
		MV1SetPosition(modelId_, pos_);
	}
}

void Player::UpdateAnim(void)
{
	// アニメーションを進める
	nowAnimTime_ += 1.0f;

	// アニメーション設定
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}
