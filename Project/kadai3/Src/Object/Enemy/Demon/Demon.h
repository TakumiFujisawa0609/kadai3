#pragma once
#include "../EnemyBase.h"

class Demon : public EnemyBase
{
public:
	Demon(void);			// コンストラクタ
	virtual ~Demon(void);	// デストラクタ

protected:
	// パラメータの設定
	void SetParam(void) override;

};

