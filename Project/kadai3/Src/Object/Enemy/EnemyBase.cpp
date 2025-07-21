#include "EnemyBase.h"
#include "../../Utility/AsoUtility.h"
#include "../Player/Player.h"
#include "../Stage/Stage.h"
#include "Bullet/Straight.h"

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

	// 生存フラグは切っておく
	isAlive_ = false;

	// アニメーション
	prevAnimType_ = ANIM_TYPE::WALK;
	nowAnimType_ = ANIM_TYPE::WALK;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;

	// パラメータの設定
	SetParam();

	// 自己発光
	MV1SetMaterialEmiColor(modelId_, 0, EMI_COLOR);

	// 大きさ変更
	MV1SetScale(modelId_, scale_);

	// 出現座標の設定
	SetSpawnPosition();

	// プレイヤーの方向を向く
	LookPlayer();

	// 初期状態
	ChangeState(STATE::MOVING);
}

void EnemyBase::Load(TYPE type, int originModelId, int originBulletModelId)
{
	// エネミー種別
	type_ = type;

	// モデルの複製
	modelId_ = MV1DuplicateModel(originModelId);

	// 弾の生成
	BulletBase* bullet = new Straight();
	bullet->Load(originBulletModelId);

	// 弾を配列に入れる
	bullets_.push_back(bullet);
}

void EnemyBase::LoadEnd(void)
{
	// アニメーション初期化(読み込み後)
	// Walkアニメーションをアタッチする
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	// アニメーションの総再生時間を取得
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);
}

void EnemyBase::Update(void)
{
	// 生存していないなら処理しない
	if (!isAlive_)
		return;

	switch (state_)
	{
	case EnemyBase::STATE::IDLE:
		break;
	case EnemyBase::STATE::MOVING:
		UpdateMoving();
		break;
	case EnemyBase::STATE::ATTACK:
		UpdateAttack();
		break;
	default:
		break;
	}

	// 弾の更新
	UpdateBullet();

	// アニメーション更新
	UpdateAnim();
}

void EnemyBase::Draw(void)
{
	// 生存していないなら処理しない
	if (!isAlive_)
		return;

	switch (state_)
	{
	case EnemyBase::STATE::IDLE:
		break;
	case EnemyBase::STATE::MOVING:
		DrawMoving();
		break;
	case EnemyBase::STATE::ATTACK:
		DrawAttack();
		break;
	default:
		break;
	}

	// 弾の描画
	DrawBullet();
}

void EnemyBase::Release(void)
{
	// モデルの削除
	MV1DeleteModel(modelId_);

	// 弾の解放
	for (BulletBase* bullet : bullets_)
	{
		bullet->Release();
		delete bullet;
	}
	bullets_.clear();
}

void EnemyBase::SetIsAlive(bool isAlive)
{
	isAlive_ = isAlive;
}

bool EnemyBase::GetIsAlive(void)
{
	return isAlive_;
}

void EnemyBase::ChangeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case EnemyBase::STATE::IDLE:
		break;
	case EnemyBase::STATE::MOVING:
		ChangeMoving();
		break;
	case EnemyBase::STATE::ATTACK:
		ChangeAttack();
		break;
	default:
		break;
	}
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

void EnemyBase::UpdateAnim(void)
{
	// アニメーションが変更された？
	if (prevAnimType_ != nowAnimType_)
	{
		// アニメーション種別を合わせる
		prevAnimType_ = nowAnimType_;

		// モデルから前回のアニメーションを外す
		MV1DetachAnim(modelId_, attachNo_);

		// 新しいアニメーションに変更する
		attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

		// アニメーション総時間の取得
		totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);

		// アニメーション時間を初期化
		nowAnimTime_ = 0.0f;
	}

	// アニメーションを進める
	nowAnimTime_ += 1.0f;

	// アニメーションをループ
	if (nowAnimTime_ > totalAnimTime_)
	{
		nowAnimTime_ = 0.0f;
	}

	// アニメーション設定
	MV1SetAttachAnimTime(modelId_, attachNo_, nowAnimTime_);
}

void EnemyBase::SetSpawnPosition(void)
{
	// ステージの半径
	float radius = Stage::STAGE_SIZE_X * 0.5f;

	// ステージの中心座標
	VECTOR centerPos = VGet(radius, 0.0f, radius);

	// ランダムな角度を取得する(360度)
	int degree = GetRand(360);
	float radian = static_cast<float>(degree) * DX_PI_F / 180.0f;

	// 角度から方向を求める
	float dirX = sinf(radian);
	float dirZ = cosf(radian);

	// ランダムな方向を半径分伸ばしたベクトル
	VECTOR vec = VScale(VGet(dirX, 0.0f, dirZ), radius);

	// 中心点の座標に加算して、ランダムな座標を求める
	VECTOR pos = VAdd(centerPos, vec);

	// 出現座標
	pos_ = pos;
	MV1SetPosition(modelId_, pos_);
}

void EnemyBase::ChangeMoving(void)
{
	// 歩くアニメーション再生
	nowAnimType_ = ANIM_TYPE::WALK;
}

void EnemyBase::ChangeAttack(void)
{
	// 攻撃アニメーション再生
	nowAnimType_ = ANIM_TYPE::ATTACK;

	// プレイヤーの方向を向く
	LookPlayer();

	// 攻撃カウンタをリセット
	attackCount_ = 0;

	// 弾を使用
	for (BulletBase* bullet : bullets_)
	{
		// 弾を使用
		bullet->CreateBullet(pos_, moveDir_);
	}
}

void EnemyBase::UpdateMoving(void)
{
	// プレイヤーの方向を向く
	LookPlayer();

	// 移動
	Move();
}

void EnemyBase::UpdateAttack(void)
{
	// アニメーションをループ
	if (nowAnimTime_ >= totalAnimTime_)
	{
		ChangeState(STATE::MOVING);
	}
}

void EnemyBase::DrawMoving(void)
{
	// 描画
	MV1DrawModel(modelId_);
}

void EnemyBase::DrawAttack(void)
{
	// 描画
	MV1DrawModel(modelId_);
}

void EnemyBase::UpdateBullet(void)
{
	// 弾の更新
	for (BulletBase* bullet : bullets_)
	{
		bullet->Update();
	}
}

void EnemyBase::DrawBullet(void)
{
	// 弾の更新
	for (BulletBase* bullet : bullets_)
	{
		bullet->Draw();
	}
}
