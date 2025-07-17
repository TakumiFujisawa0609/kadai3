#pragma once
#include "BulletBase.h"

class Straight : public BulletBase
{

public:

	// コンストラクタ(元となるモデルのハンドルID)
	Straight(void);

	// デストラクタ
	virtual ~Straight(void);

private:

	// パラメータ設定
	void SetParam(void) override;

};
