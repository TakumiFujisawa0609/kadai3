#pragma once
#include <DxLib.h>

class EnemyBase
{

public:

	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	~EnemyBase(void);

	// 初期処理
	void Init(void);

	// 読み込み
	void Load(void);

	// 読み込み後
	void LoadEnd(void);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);

private:
	// モデルのハンドルID
	int modelId_;

	// 座標
	VECTOR pos_;
	// 角度
	VECTOR angle_;
	// 大きさ
	VECTOR scale_;

};


