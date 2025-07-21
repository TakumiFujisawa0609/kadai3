#include "Wizard.h"

Wizard::Wizard(void)
{
}

Wizard::~Wizard(void)
{
}

void Wizard::SetParam(void)
{
	hp_ = 1;
	collRadius_ = 50.0f;
	spawnRange_ = 0.8f;
	scale_ = { 0.5f, 0.5f, 0.5f };
	speed_ = 0.0f;
}

void Wizard::UpdateMoving(void)
{
	// プレイヤーの方向を向く
	LookPlayer();

	// 攻撃カウンタの加算
	attackCount_++;

	// カウンタが攻撃状態になったら
	if (attackCount_ > ATTACK_INTERVAL)
	{
		// カウンタの初期化
		attackCount_ = 0;

		// 攻撃状態へ
		ChangeState(STATE::ATTACK);
	}
}
