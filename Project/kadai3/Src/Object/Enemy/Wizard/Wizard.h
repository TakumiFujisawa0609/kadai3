#pragma once
#include "../EnemyBase.h"

class Wizard : public EnemyBase
{
public:
	Wizard(void);			// コンストラクタ
	virtual ~Wizard(void);	// デストラクタ

protected:
	// パラメータの設定
	void SetParam(void) override;

};