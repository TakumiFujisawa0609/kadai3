#pragma once
#include <DxLib.h>

class Player
{

public:

	// モデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	// 初期位置
	static constexpr VECTOR INIT_POS = { 300.0f, 10.0f, 300.0f };
	// 標準の自己発光色
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 0.5f };

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
		
	int modelId_;	// モデルのハンドルID
	VECTOR pos_;	// 座標
	VECTOR angle_;	// 向き
	VECTOR scale_;	// 大きさ
};
