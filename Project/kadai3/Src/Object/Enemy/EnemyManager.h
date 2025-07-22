#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Bullet/BulletBase.h"

class EnemyBase;
class Player;

class EnemyManager
{
public:
	// 定数
	// 最大の敵の数
	static constexpr int ENEMY_MAX_NUM = 10;

	// 敵の出現感覚
	static constexpr int SPAWN_INTERVAL = 200;

public:
	EnemyManager(void);		// コンストラクタ
	~EnemyManager(void);	// デストラクタ

	void Init(Player* player);		// 初期化
	void Load(void);		// 読み込み
	void LoadEnd(void);		// 読み込み後
	void Update(void);		// 更新
	void Draw(void);		// 描画
	void Release(void);		// 解放

	// 全ての敵を取得
	std::vector<EnemyBase*> GetEnemys(void);

private:
	// エネミー用のモデルハンドルID
	int originModelId_[static_cast<int>(EnemyBase::TYPE::MAX)];

	// エネミーをまとめる動的配列
	std::vector<EnemyBase*> enemys_;

	// 弾用のモデルハンドルID
	int originBulletModelId_[static_cast<int>(BulletBase::TYPE::MAX)];

	// プレイヤーの情報アドレス
	Player* player_;

	// 出現間隔
	int spawnInterval_;

};
