#pragma once
#include "../EnemyBase.h"

class Wizard : public EnemyBase
{
public:
	// 攻撃間隔(1秒 = 60fps)
	static constexpr int ATTACK_INTERVAL = 120;

public:
	Wizard(void);			// コンストラクタ
	virtual ~Wizard(void);	// デストラクタ

protected:
	// パラメータの設定
	void SetParam(void) override;

	// 状態別更新
	void UpdateMoving(void) override;
};