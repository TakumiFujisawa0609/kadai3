#include <DxLib.h>
#include "GameScene.h"
#include "../../Object/Grid/Grid.h"
#include "../../Camera/Camera.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"

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
	camera_->Init();

	// ステージ初期化
	stage_->Init();

	// プレイヤーの初期化
	player_->Init();
}

// 読み込み
void GameScene::Load(void)
{
	// グリッドの生成
	grid_ = new Grid();

	// カメラの生成
	camera_ = new Camera();

	// ステージの生成
	stage_ = new Stage();
	stage_->Load();

	// プレイヤーの生成
	player_ = new Player();
	player_->Load();
}

// 読み込み後の初期化
void GameScene::LoadEnd(void)
{
	// 初期化
	Init();

	stage_->LoadEnd();
	player_->LoadEnd();
}

// 更新
void GameScene::Update(void)
{
	// グリッド更新
	grid_->Update();

	// カメラ更新
	camera_->Update();

	// ステージ更新
	stage_->Update();

	// プレイヤーの更新
	player_->Update();
}

// 描画
void GameScene::Draw(void)
{
	// グリッド描画
	grid_->Draw();

	// カメラ描画
	camera_->SetBeforeDraw();
	camera_->DrawDebug();

	// ステージ描画
	stage_->Draw();

	// プレイヤーの描画
	player_->Draw();
}

// 解放
void GameScene::Release(void)
{
	// グリッド解放
	grid_->Release();
	delete grid_;

	// カメラ解放
	camera_->Release();
	delete camera_;

	// ステージ解放
	stage_->Release();
	delete stage_;

	// プレイヤーの解放
	player_->Release();
	delete player_;
}
