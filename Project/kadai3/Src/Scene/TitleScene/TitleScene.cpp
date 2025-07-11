#include <DxLib.h>

#include "TitleScene.h"
#include "../../Application/Application.h"
#include "../../UI/UIButton.h"
#include "../../Input/InputManager.h"
#include "../../Scene/SceneManager/SceneManager.h"

// コンストラクタ
TitleScene::TitleScene(void)
{}

// デストラクタ
TitleScene::~TitleScene(void)
{}

// 初期化
void TitleScene::Init(void)
{
}

// 読み込み
void TitleScene::Load(void)
{
	handle_ = LoadGraph("Data/Image/Title.png");
	
	// ボタン作成
	button_ = new UIButton(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 + 240,
		258,
		88
	);

	button_->Load();
}

// 読み込み後の処理
void TitleScene::LoadEnd(void)
{
	// 初期化
	Init();
	button_->Init();
}

// 更新
void TitleScene::Update(void)
{
	button_->Update();

	// 次のシーンへ遷移する関数
	toNextScene();
}

// 描画
void TitleScene::Draw(void)
{
	DrawExtendGraph(
		0,
		0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		handle_,
		true
	);

	button_->Draw();
}

// 解放
void TitleScene::Release(void)
{
	DeleteGraph(handle_);
}

// 次のシーンへ遷移
void TitleScene::toNextScene(void)
{
	// シーン遷移
	// スペースキーを押す もしくは ボタンをクリックをすると遷移する！
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_SPACE) ||
		button_->GetButtonState() == BUTTON_STATE::AFTER_CLICK)
	{
		SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}
