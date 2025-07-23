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

	// ジャンプ力の初期化
	jumpPow_ = 0.0f;

	// ジャンプフラグの初期化
	isJump_ = false;

	// アニメーション
	prevAnimType_ = ANIM_TYPE::IDEL;
	nowAnimType_ = ANIM_TYPE::IDEL;
	attachNo_ = 0;
	nowAnimTime_ = 0.0f;
	totalAnimTime_ = 0.0f;

	// 初期状態
	ChangeState(STATE::MOVE);
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
	attachNo_ = MV1AttachAnim(modelId_, static_cast<int>(nowAnimType_));

	// アニメーションの総再生時間を取得
	totalAnimTime_ = MV1GetAttachAnimTotalTime(modelId_, attachNo_);
}

void Player::Update(void)
{
	switch (state_)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::MOVE:
		UpdateMove();
		break;
	case Player::STATE::KNOCKBACK:
		UpdateKnockback();
		break;
	case Player::STATE::ATTACK:
		UpdateAttack();
		break;
	case Player::STATE::DEAD:
		UpdateDead();
		break;
	case Player::STATE::END:
		UpdateEnd();
		break;
	case Player::STATE::VICTORY:
		UpdateVictory();
		break;
	}

	// 衝突判定前の落下制御
	if (pos_.y < RESPAWN_DIS)
	{
		// 初期化
		Init();
	}

	// アニメーションの更新
	UpdateAnim();

	// カメラに自身の座標を渡す
	Camera::GetInstance()->SetFollowPos(pos_);
}

void Player::Draw(void)
{

	switch (state_)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::MOVE:
		DrawMove();
		break;
	case Player::STATE::KNOCKBACK:
		DrawKnockback();
		break;
	case Player::STATE::ATTACK:
		DrawAttack();
		break;
	case Player::STATE::DEAD:
		DrawDead();
		break;
	case Player::STATE::END:
		DrawEnd();
		break;
	case Player::STATE::VICTORY:
		DrawVictory();
		break;
	default:
		break;
	}
}

void Player::Release(void)
{
	// モデルの削除
	MV1DeleteModel(modelId_);
}

VECTOR Player::GetPos(void)
{
	return pos_;
}

void Player::CollisionStage(VECTOR pos)
{
	// 衝突した位置
	pos_ = pos;
	jumpPow_ = 0.0f;
	isJump_ = false;
}

void Player::KnockBack(VECTOR dirXZ, float jumpPow)
{
	// 引数をメンバ変数に格納
	knockBackDir_ = dirXZ;
	jumpPow_ = jumpPow;

	// ノックバックに状態遷移
	ChangeState(STATE::KNOCKBACK);
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

		// アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::WALK;
	}
	// 移動していない
	else
	{
		// アニメーションを変更する
		nowAnimType_ = ANIM_TYPE::IDEL;
	}
}

void Player::ProcessJump(void)
{
	// 重力
	jumpPow_ -= GRAVITY;

	// ジャンプ
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_SPACE) && !isJump_)
	{
		isJump_ = true;
		jumpPow_ = JUMP_POW;

		// ジャンプアニメーション再生
		nowAnimType_ = ANIM_TYPE::JUMP;
	}

	// プレイヤーの座標にジャンプ力を加算する
	pos_.y += jumpPow_;

	// モデルに座標を設定する
	MV1SetPosition(modelId_, pos_);
}

void Player::UpdateAnim(void)
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

void Player::ChangeState(STATE state)
{
	state_ = state;

	switch (state)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::MOVE:
		ChangeMove();
		break;
	case Player::STATE::KNOCKBACK:
		ChangeKnockback();
		break;
	case Player::STATE::ATTACK:
		ChangeAttack();
		break;
	case Player::STATE::DEAD:
		ChangeDead();
		break;
	case Player::STATE::END:
		ChangeEnd();
		break;
	case Player::STATE::VICTORY:
		ChangeVictory();
		break;
	default:
		break;
	}
}

void Player::ChangeMove(void)
{
	// 拡散光を標準値に戻す
	MV1SetMaterialDifColor(modelId_, 0, DIF_COLOR_DEF);
}

void Player::ChangeKnockback(void)
{
	// ジャンプ判定にする
	isJump_ = true;

	// ノックバックカウンタリセット
	knockBackCount_ = 0;
}

void Player::ChangeAttack(void)
{
}

void Player::ChangeDead(void)
{
}

void Player::ChangeEnd(void)
{
}

void Player::ChangeVictory(void)
{
}

void Player::UpdateMove(void)
{
	// 移動操作
	ProcessMove();

	// ジャンプ
	ProcessJump();
}

void Player::UpdateKnockback(void)
{
	// 着地したら通常状態に戻す
	if (!isJump_)
	{
		ChangeState(STATE::MOVE);
		return;
	}

	knockBackCount_++;

	// ジャンプする
	jumpPow_ -= GRAVITY;

	pos_.y += jumpPow_;

	// ノックバック方向に移動させる
	pos_ = VAdd(pos_, VScale(knockBackDir_, KNOCKBACK_SPEED));
	MV1SetPosition(modelId_, pos_);

}

void Player::UpdateAttack(void)
{
}

void Player::UpdateDead(void)
{
}

void Player::UpdateEnd(void)
{
}

void Player::UpdateVictory(void)
{
}

void Player::DrawMove(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::DrawKnockback(void)
{
	// モデルの点滅処理
	if (knockBackCount_ % BLINK_INTERVAL == 0)
	{
		MV1SetMaterialDifColor(modelId_, 0, DIF_COLOR_DEF);
	}
	else
	{
		MV1SetMaterialDifColor(modelId_, 0, DIF_COLOR_BLINK);
	}

	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::DrawAttack(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::DrawDead(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::DrawEnd(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}

void Player::DrawVictory(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}
