#pragma once
#include <DxLib.h>

class Player
{
public:
	// アニメーション種別
	enum class ANIM_TYPE
	{
		DEAD = 0,	// 死亡
		IDEL = 3,	// 待機
		WALK = 14,	// 歩き
	};

public:

	// モデルの大きさ
	static constexpr VECTOR SCALE = { 0.5f, 0.5f, 0.5f };
	// 初期位置
	static constexpr VECTOR INIT_POS = { 300.0f, 10.0f, 300.0f };
	// 標準の自己発光色
	static constexpr COLOR_F EMI_COLOR = { 0.5f, 0.5f, 0.5f, 0.5f };

	// 移動スピード
	static constexpr float MOVE_SPEED = 10.0f;

	// 重力
	static constexpr float GRAVITY = 0.8f;

	// 地面衝突判定用の線分の長さ
	static constexpr float COLL_LEN = 10.0f;

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

	// 座標の取得
	VECTOR GetPos(void);

	// 衝突判定
	void CollisionStage(VECTOR pos);

private:
	// 移動制御
	void ProcessMove(void);

	// ジャンプ制御
	void ProcessJump(void);

	// アニメーション再生
	void UpdateAnim(void);

private:
		
	int modelId_;	// モデルのハンドルID
	VECTOR pos_;	// 座標
	VECTOR angle_;	// 向き
	VECTOR scale_;	// 大きさ
	float jumpPow_;	// ジャンプ力

	// アニメーション
	ANIM_TYPE prevAnimType_;	// 前回のアニメーション種別
	ANIM_TYPE nowAnimType_;		// 現在のアニメーション種別

	int attachNo_;				// アタッチNo
	float nowAnimTime_;			// 再生中の時間
	float totalAnimTime_;		// 総再生時間
};
