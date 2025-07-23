#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyManager.h"
#include "../../Utility/AsoUtility.h"


// コンストラクタ
GameScene::GameScene()
{
}

// デストラクタ
GameScene::~GameScene()
{
}

// 初期化
void GameScene::Init(void)
{
	// グリッド初期化
	grid_->Init();

	// カメラ初期化
	Camera::GetInstance()->Init();

	// ステージ初期化
	stage_->Init();

	// プレイヤーの初期化
	player_->Init();

	// エネミー管理の初期化
	enemyManager_->Init(player_);
}

// 読み込み
void GameScene::Load(void)
{
	// グリッドの生成
	grid_ = new Grid();

	// カメラの生成
	Camera::CreateInstance();

	// ステージの生成
	stage_ = new Stage();
	stage_->Load();

	// プレイヤーの生成
	player_ = new Player();
	player_->Load();

	// エネミー管理の生成
	enemyManager_ = new EnemyManager();
	enemyManager_->Load();
}

// 読み込み後の初期化
void GameScene::LoadEnd(void)
{
	// 初期化
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
	enemyManager_->LoadEnd();
}

// 更新
void GameScene::Update(void)
{
	// グリッド更新
	grid_->Update();

	// カメラ更新
	Camera::GetInstance()->Update();

	// ステージ更新
	stage_->Update();

	// プレイヤーの更新
	player_->Update();

	// エネミー管理の更新
	enemyManager_->Update();

	// 衝突判定
	Collision();
}

// 描画
void GameScene::Draw(void)
{
	// グリッド描画
	grid_->Draw();

	// カメラ描画
	Camera::GetInstance()->SetBeforeDraw();
	Camera::GetInstance()->DrawDebug();

	// ステージ描画
	stage_->Draw();

	// プレイヤーの描画
	player_->Draw();

	// エネミー管理の描画
	enemyManager_->Draw();

	// デバッグ描画
	DebugDraw();
}

// 解放
void GameScene::Release(void)
{
	// グリッド解放
	grid_->Release();
	delete grid_;

	// カメラ解放
	Camera::GetInstance()->Release();
	Camera::DeleteInstance();

	// ステージ解放
	stage_->Release();
	delete stage_;

	// プレイヤーの解放
	player_->Release();
	delete player_;

	// エネミー管理の解放
	enemyManager_->Release();
	delete enemyManager_;
}

void GameScene::DebugDraw(void)
{
	// 地面との衝突用線分
	DrawSphere3D(lineTopPos_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
	DrawSphere3D(lineDownPos_, 20.0f, 10, 0x00ff00, 0x00ff00, true);
	DrawLine3D(lineTopPos_, lineDownPos_, 0xff0000);
}

void GameScene::Collision(void)
{
	// ステージブロックとプレイヤーの衝突
	CollisionStage();

	// エネミーとプレイヤーの衝突
	CollisionEnemy();
}

void GameScene::CollisionStage(void)
{
	// ステージブロックとプレイヤーの衝突
	VECTOR playerPos = player_->GetPos();

	// 線分の上座標
	VECTOR topPos = playerPos;
	topPos.y = playerPos.y + (Player::COLL_LEN * 2.0f);
	lineTopPos_ = topPos;

	// 線分の下座標
	VECTOR downPos = playerPos;
	downPos.y = playerPos.y - Player::COLL_LEN;
	lineDownPos_ = downPos;

	// 線分とブロックモデルの衝突判定
	MV1_COLL_RESULT_POLY result;
	if (stage_->IsCollisionLine(topPos, downPos, &result))
	{
		// プレイヤーに衝突座標を渡す
		player_->CollisionStage(result.HitPosition);
	}
}

void GameScene::CollisionEnemy(void)
{
	// プレイヤーの座標
	VECTOR playerPos = player_->GetPos();

	// 敵の情報を取得
	std::vector<EnemyBase*> enemys = enemyManager_->GetEnemys();

	// 敵を全て検索
	for (EnemyBase* enemy : enemys)
	{
		// 敵が生存していないなら無視する
		if (!enemy->GetIsAlive())
			continue;

		// 敵の座標
		VECTOR enemyPos = enemy->GetPos();

		// 敵とプレイヤーの衝突判定(球体)
		if (AsoUtility::IsHitSpheres(
			playerPos,
			Player::COLL_RADIUS,
			enemyPos,
			enemy->GetCollRadius()
		))
		{
			// ノックバックするXZ方向を求める
			VECTOR diff = VSub(playerPos, enemyPos);
			diff.y = 0.0f;
			VECTOR dir = VNorm(diff);
			// プレイヤーをノックバックさせる
			player_->KnockBack(dir, 20.0f);
		}

		// 弾を取得
		std::vector<BulletBase*> bullets = enemy->GetBullets();

		// 全ての弾を検索
		for (BulletBase* bullet : bullets)
		{
			// 弾の座標
			VECTOR bulletPos = bullet->GetPos();

			// 敵の弾とプレイヤーの衝突判定(球体)
			if (AsoUtility::IsHitSpheres(
				playerPos,
				Player::COLL_RADIUS,
				bulletPos,
				bullet->GetCollisionRadius()
			))
			{
				// ノックバックするXZ方向を求める
				VECTOR diff = VSub(playerPos, bulletPos);
				diff.y = 0.0f;
				VECTOR dir = VNorm(diff);
				// プレイヤーをノックバックさせる
				player_->KnockBack(dir, 20.0f);
			}
		}
	}
}
