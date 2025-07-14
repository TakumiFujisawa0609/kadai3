#pragma once
#include <DxLib.h>

// クラスの前方宣言
class Player;

class EnemyBase
{

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

private:
	// プレイヤーの方向を向く
	void LookPlayer(void);

	// 移動
	void Move(void);

private:
	// プレイヤーの情報アドレス
	Player* player_;

	// モデルのハンドルID
	int modelId_;

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

};


