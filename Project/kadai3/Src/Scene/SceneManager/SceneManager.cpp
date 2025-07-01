#include <DxLib.h>
#include "SceneManager.h"
#include "../../Scene/TitleScene/TitleScene.h"
#include "../../Scene/GameScene/GameScene.h"

#include "../../Loading/Loading.h"

SceneManager* SceneManager::instance_ = nullptr;

// コンストラクタ
SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	scene_ = nullptr;
	isGameEnd_ = false;
}

// デストラクタ
SceneManager::~SceneManager(void)
{
}

// 初期化
void SceneManager::Init(void)
{
	// ロード画面生成
	Loading::GetInstance()->CreateInstance();
	Loading::GetInstance()->Init();
	Loading::GetInstance()->Load();

	// 3D情報の初期化
	Init3D();

	// 最初はタイトル画面から
	ChangeScene(SCENE_ID::TITLE);
}

// 3D情報の初期化
void SceneManager::Init3D(void)
{
	// 背景色設定
	SetBackgroundColor(0, 0, 0);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// 正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });
}

// 更新
void SceneManager::Update(void)
{
	// シーンがなければ終了
	if (scene_ == nullptr) { return; }

	// ロード中
	if (Loading::GetInstance()->IsLoading())
	{
		// ロード更新
		Loading::GetInstance()->Update();

		// ロードの更新が終了していたら
		if (Loading::GetInstance()->IsLoading() == false)
		{
			// ロード後の初期化
			scene_->LoadEnd();
		}
	}		
	// 通常の更新処理
	else
	{
		// 現在のシーンの更新
		scene_->Update();
	}
}

// 描画
void SceneManager::Draw(void)
{
	// ロード中ならロード画面を描画
	if (Loading::GetInstance()->IsLoading())
	{
		// ロードの描画
		Loading::GetInstance()->Draw();
	}
	// 通常の更新
	else
	{
		//　現在のシーン描画
		scene_->Draw();
	}
}

// 解放
void SceneManager::Release(void)
{
	// 現在のシーンの解放・削除
	scene_->Release();
	delete scene_;

	// ロード画面の削除
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();
}

// 状態遷移関数
void SceneManager::ChangeScene(SCENE_ID nextId)
{
	// シーンを変更する
	sceneId_ = nextId;

	// 現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	// 各シーンに切り替え
	switch (sceneId_)
	{
	case SceneManager::SCENE_ID::NONE:
		break;
	case SceneManager::SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SceneManager::SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	default:
		break;
	}

	// 読み込み(非同期)
	Loading::GetInstance()->StartAsyncLoad();
	scene_->Load();
	Loading::GetInstance()->EndAsyncLoad();
}
