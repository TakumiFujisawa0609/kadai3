#pragma once
#include <DxLib.h>

// クラスの前方宣言
class Player;

class EnemyBase
{
public:
	// アニメーション種別
	enum class ANIM_TYPE
	{
		WALK = 6,	// 歩き
	};

public:

	// コンストラクタ
	EnemyBase(void);

	// デストラクタ
	~EnemyBase(void);

	// 初期処理
	void Init(Player* player);

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

	// 生存フラグを立てる
	void SetIsAlive(bool isAlive);

	// 生存フラグを取得する
	bool GetIsAlive(void);

private:
	// プレイヤーの方向を向く
	void LookPlayer(void);

	// 移動
	void Move(void);

	// アニメーション再生
	void UpdateAnim(void);

	// 出現座標の設定
	void SetSpawnPosition(void);

private:
	// プレイヤーの情報アドレス
	Player* player_;

	// モデルのハンドルID
	int modelId_;

	// 生存フラグ
	bool isAlive_;

	// 座標
	VECTOR pos_;
	// 角度
	VECTOR angle_;
	// 大きさ
	VECTOR scale_;
	// 移動方向
	VECTOR moveDir_;
	// 移動速度
	float speed_;

	// アニメーション
	ANIM_TYPE prevAnimType_;	// 前回のアニメーション種別
	ANIM_TYPE nowAnimType_;		// 現在のアニメーション種別

	int attachNo_;				// アタッチNo
	float nowAnimTime_;			// 再生中の時間
	float totalAnimTime_;		// 総再生時間

};


