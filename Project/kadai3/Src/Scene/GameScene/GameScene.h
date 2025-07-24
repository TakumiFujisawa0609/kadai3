#pragma once
#include "../SceneBase.h"

// 前方宣言
class Grid;
class Stage;
class Player;
class EnemyManager;

// ベースを継承
class GameScene : public SceneBase
{
public:

	GameScene();			// コンストラクタ
	~GameScene() override;	// デストラクタ

public:
	void Init(void)		override;	// 初期化
	void Load(void)		override;	// 読み込み
	void LoadEnd(void)	override;	// 読み込み後の初期化
	void Update(void)	override;	// 更新
	void Draw(void)		override;	// 描画
	void Release(void)	override;	// 解放

private:
	// デバッグ描画
	void DebugDraw(void);

	// 衝突判定
	void Collision(void);

	// ステージとプレイヤーの衝突判定
	void CollisionStage(void);

	// エネミーとプレイヤーの衝突判定
	void CollisionEnemy(void);

	// エネミーとプレイヤーの攻撃の衝突判定
	void CollisionAttack(void);

private:
	Grid* grid_;		// グリッドクラス(デバッグ用)

	EnemyManager* enemyManager_;	// エネミー管理
	Stage* stage_;					// ステージ管理
	Player* player_;				// プレイヤー

	// 地面との衝突用線分
	VECTOR lineTopPos_;
	VECTOR lineDownPos_;
};
