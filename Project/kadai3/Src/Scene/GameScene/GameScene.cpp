#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"

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

	// エネミーの初期化
	enemy_->Init(player_);
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

	// エネミーの生成
	enemy_ = new EnemyBase();
	enemy_->Load();
}

// 読み込み後の初期化
void GameScene::LoadEnd(void)
{
	// 初期化
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
	enemy_->LoadEnd();
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

	// エネミーの更新
	enemy_->Update();

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

	// エネミーの描画
	enemy_->Draw();

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

	// エネミーの解放
	enemy_->Release();
	delete enemy_;
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
