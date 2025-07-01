#include <DxLib.h>

#include "TitleScene.h"
#include "../../Application/Application.h"

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
}

// 読み込み後の処理
void TitleScene::LoadEnd(void)
{
	// 初期化
	Init();
}

// 更新
void TitleScene::Update(void)
{
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
}

// 解放
void TitleScene::Release(void)
{
	DeleteGraph(handle_);
}

// 次のシーンへ遷移
void TitleScene::toNextScene(void)
{
}
