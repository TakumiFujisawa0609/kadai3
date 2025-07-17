#pragma once
#include <DxLib.h>

class BulletBase
{

public:

	// 弾の種類
	enum class TYPE
	{
		STRAIGHT,

		MAX,
	};
	
	BulletBase(void);			// コンストラクタ
	virtual ~BulletBase(void);	// デストラクタ

	void Load(int originHandle);// 読み込み
	void LoadEnd(void);			// 読み込み後
	virtual void Update(void);	// 更新
	void Draw(void);			// 描画
	void Release(void);			// 解放

	// 弾の生成(表示開始座標、弾の進行方向)
	virtual void CreateBullet(VECTOR pos, VECTOR dir);

	// 生存判定
	bool GetIsAlive(void);

	// 弾の座標
	VECTOR GetPos(void);

	// 弾の衝突判定用半径
	float GetCollisionRadius(void);

protected:

	// 弾のモデルID
	int modelId_;

	// 方向
	VECTOR dir_;

	// 弾の大きさ
	VECTOR scale_;

	// 弾の座標
	VECTOR pos_;

	// 弾の移動速度
	float speed_;

	// 弾の生存判定
	bool isAlive_;

	// 弾の生存期間
	int cntAlive_;

	// 弾の衝突判定用半径
	float collisionRadius_;

	// パラメータ設定
	virtual void SetParam(void) = 0;

	// 弾の生存期間の減少
	void ReduceCntAlive(void);

};
