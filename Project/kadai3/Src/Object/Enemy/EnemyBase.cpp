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
	// プレイヤーのポイントを取得
	player_ = player;

	// 移動速度の初期化
	speed_ = 5.0f;

	// プレイヤーの方向を向く
	LookPlayer();
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
	// プレイヤーの方向を向く
	LookPlayer();

	// 移動
	Move();
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

void EnemyBase::LookPlayer(void)
{
	// プレイヤーの向きを計算
	VECTOR diff = VSub(player_->GetPos(), pos_);
	diff.y = 0.0f;
	// ベクトルを正規化(向きのみの情報に変換)
	moveDir_ = VNorm(diff);

	// 方向を角度に変換(xとz軸は回さない)
	angle_.x = 0.0f;
	angle_.z = 0.0f;
	angle_.y = atan2f(moveDir_.x, moveDir_.z);
	
	// モデルが逆方面を向いているのでY軸を反転させる
	angle_.y += AsoUtility::Deg2RadF(180.0f);

	// モデルの回転を反映させる
	MV1SetRotationXYZ(modelId_, angle_);
}

void EnemyBase::Move(void)
{
	// 移動処理
	pos_ = VAdd(pos_, VScale(moveDir_, speed_));

	// 敵の移動制限
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

	// モデルの座標を反映させる
	MV1SetPosition(modelId_, pos_);
}
