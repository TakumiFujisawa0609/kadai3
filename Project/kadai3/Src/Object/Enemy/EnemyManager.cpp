#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Demon/Demon.h"

EnemyManager::EnemyManager(void)
{
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(Player* player)
{
	player_ = player;

	// 出現間隔の初期化
	spawnInterval_ = 0;

	// すべてのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		// 初期化
		enemy->Init(player_);
	}
}

void EnemyManager::Load(void)
{
	// エネミーの生成
	// エネミーの最大数分確保しておく
	for (int i = 0; i < ENEMY_MAX_NUM; i++)
	{
		// デーモンを生成
		EnemyBase* enemy = new Demon();
		enemy->Load();

		// 作成したエネミーを配列に入れる
		enemys_.push_back(enemy);
	}
}

void EnemyManager::LoadEnd(void)
{
	// すべてのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		// 更新
		enemy->LoadEnd();
	}
}

void EnemyManager::Update(void)
{
	// 出現インターバルを加算
	spawnInterval_++;

	// 一定間隔でエネミーを出現させる
	if (spawnInterval_ > SPAWN_INTERVAL)
	{
		// エネミーの生存フラグを立てる
		// すべてのエネミーを回す
		for (EnemyBase* enemy : enemys_)
		{
			// 生存していない敵を検索
			if (!enemy->GetIsAlive())
			{
				// 生存フラグを立てる
				enemy->SetIsAlive(true);

				// 出現インターバルを初期化
				spawnInterval_ = 0;

				// ループを抜ける
				break;
			}
		}
	}

	// すべてのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		// 生存していないなら処理しない
		if (!enemy->GetIsAlive())
			continue;

		// 更新
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	// すべてのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		// 生存していないなら処理しない
		if (!enemy->GetIsAlive())
			continue;

		// 描画
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	// すべてのエネミーを回す
	for (EnemyBase* enemy : enemys_)
	{
		// 解放
		enemy->Release();
	}
}
