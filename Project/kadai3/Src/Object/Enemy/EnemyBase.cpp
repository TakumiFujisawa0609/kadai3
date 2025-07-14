#include "EnemyBase.h"
#include "../../Utility/AsoUtility.h"
#include "../Player/Player.h"

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
