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

	// 移動スピード
	static constexpr float MOVE_SPEED = 10.0f;

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
	// 移動制御
	void ProcessMove(void);

	// アニメーション再生
	void UpdateAnim(void);

private:
		
	int modelId_;	// モデルのハンドルID
	VECTOR pos_;	// 座標
	VECTOR angle_;	// 向き
	VECTOR scale_;	// 大きさ

	// アニメーション
	int attachNo_;			// アタッチNo
	float nowAnimTime_;		// 再生中の時間
	float totalAnimTime_;	// 総再生時間
};
