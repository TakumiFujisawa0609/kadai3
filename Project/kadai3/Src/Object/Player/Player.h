#pragma once
#include <DxLib.h>

class Player
{
public:
	// 状態
	enum class STATE
	{
		NONE,
		MOVE,
		KNOCKBACK,
		ATTACK,
		DEAD,
		END,
		VICTORY,
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		DEAD = 0,	// 死亡
		IDEL = 3,	// 待機
		JUMP = 6,	// ジャンプ
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

	// 当たり判定の半径
	static constexpr float COLL_RADIUS = 50.0f;

	// ノックバックのスピード
	static constexpr float KNOCKBACK_SPEED = 10.0f;

	// ジャンプ力
	static constexpr float JUMP_POW = 20.0f;

	// リスポーン判定距離
	static constexpr float RESPAWN_DIS = -1500.0f;

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

	// 指定の方向にノックバックする
	void KnockBack(VECTOR dirXZ, float jumpPow);

private:
	// 移動制御
	void ProcessMove(void);

	// ジャンプ制御
	void ProcessJump(void);

	// アニメーション再生
	void UpdateAnim(void);

	// 状態遷移
	void ChangeState(STATE state);

	// 状態別遷移
	void ChangeMove(void);
	void ChangeKnockback(void);
	void ChangeAttack(void);
	void ChangeDead(void);
	void ChangeEnd(void);
	void ChangeVictory(void);

	// 状態別更新
	void UpdateMove(void);
	void UpdateKnockback(void);
	void UpdateAttack(void);
	void UpdateDead(void);
	void UpdateEnd(void);
	void UpdateVictory(void);

	// 状態別描画
	void DrawMove(void);
	void DrawKnockback(void);
	void DrawAttack(void);
	void DrawDead(void);
	void DrawEnd(void);
	void DrawVictory(void);

private:

	// 状態
	STATE state_;
		
	int modelId_;	// モデルのハンドルID
	VECTOR pos_;	// 座標
	VECTOR angle_;	// 向き
	VECTOR scale_;	// 大きさ
	float jumpPow_;	// ジャンプ力
	bool isJump_;	// ジャンプ判定

	// ノックバック方向
	VECTOR knockBackDir_;

	// ノックバックカウンタ(点滅用)
	int knockBackCount_;

	// アニメーション
	ANIM_TYPE prevAnimType_;	// 前回のアニメーション種別
	ANIM_TYPE nowAnimType_;		// 現在のアニメーション種別

	int attachNo_;				// アタッチNo
	float nowAnimTime_;			// 再生中の時間
	float totalAnimTime_;		// 総再生時間
};
