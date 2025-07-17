#pragma once
#include <DxLib.h>
#include <vector>


// クラスの前方宣言
class Player;
class BulletBase;

class EnemyBase
{
public:
	// エネミー種別
	enum class TYPE
	{
		DEMON,	// 悪魔
		WIZARD,	// 魔法使い
		GIANT,	// 巨人
		MAX,
	};

	// 状態
	enum class STATE
	{
		IDLE,	// 待機
		MOVING,	// 移動
		ATTACK,	// 攻撃
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		ATTACK,	// 攻撃
		DEAD,	// 死亡
		HIT,	// ヒット
		IDLE,	// 待機
		JUMP,	// ジャンプ
		RUN,	// 走る
		WALK,	// 歩き
		MAX
	};

public:
	// 定数
	// 自己発光
	static constexpr COLOR_F EMI_COLOR = { 0.6f,0.6f,0.6f,1.0f };

public:

	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	virtual ~EnemyBase(void);

	// 初期処理
	void Init(Player* player);

	// 読み込み
	void Load(TYPE type, int originModelId, int originBulletModelId);

	// 読み込み後
	void LoadEnd(void);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// 解放処理
	void Release(void);

	// 生存フラグを立てる
	void SetIsAlive(bool isAlive);

	// 生存フラグを取得する
	bool GetIsAlive(void);

	// 状態遷移
	void ChangeState(STATE state);

private:
	// プレイヤーの方向を向く
	void LookPlayer(void);

	// 移動
	void Move(void);

	// アニメーション再生
	void UpdateAnim(void);

	// 出現座標の設定
	void SetSpawnPosition(void);

protected:
	// パラメータの設定(純粋仮想関数)
	virtual void SetParam(void) = 0;

	// 状態遷移
	virtual void ChangeMoving(void);
	virtual void ChangeAttack(void);

	// 状態別更新
	virtual void UpdateMoving(void);
	virtual void UpdateAttack(void);

	// 状態別描画
	virtual void DrawMoving(void);
	virtual void DrawAttack(void);

	// 弾の更新
	void UpdateBullet(void);

	// 弾の描画
	void DrawBullet(void);

	// 有効な弾を取得
	BulletBase* GetValidBullet(void);

protected:
	// 衝突判定用半径
	float collRadius_;

	// 出現範囲(半径)
	float spawnRange_;

	// 体力
	int hp_;

	// 移動速度
	float speed_;

	// プレイヤーの情報アドレス
	Player* player_;

	// モデルのハンドルID
	int modelId_;

	// 生存フラグ
	bool isAlive_;

	// 種別
	TYPE type_;

	// 状態
	STATE state_;

	// 座標
	VECTOR pos_;
	// 角度
	VECTOR angle_;
	// 大きさ
	VECTOR scale_;
	// 移動方向
	VECTOR moveDir_;

	// アニメーション
	ANIM_TYPE prevAnimType_;	// 前回のアニメーション種別
	ANIM_TYPE nowAnimType_;		// 現在のアニメーション種別

	int attachNo_;				// アタッチNo
	float nowAnimTime_;			// 再生中の時間
	float totalAnimTime_;		// 総再生時間

	// 攻撃
	int attackCount_;

	// 弾
	std::vector<BulletBase*> bullets_;

	// エフェクト用モデルハンドルID
	int baseBulletModelId_;

};


