#include <DxLib.h>
#include "Application.h"
#include "../FpsControl/FpsControl.h"

Application* Application::instance_ = nullptr;

// コンストラクタ
Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}

// デストラクタ
Application::~Application(void)
{
}

// 初期化
void Application::Init(void)
{
	// アプリケーションの初期設定
	SetWindowText("Kadai3");

	// ウィンドウ関連
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);	// サイズ変更
	ChangeWindowMode(true);	// false = フルスクリーン

	// DxLibの初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		// 初期化失敗
		isInitFail_ = true;
		return;
	}

	// 描画先画面を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	// キー制御初期化
	SetUseDirectInputFlag(true);

	// FPS初期化
	fps_ = new FpsControl;
	fps_->Init();
}

// ゲームループ
void Application::Run(void)
{
	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// エスケープキーが押されたらゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) return;

		// フレームレート更新
		// 1/60秒経過していないなら再ループさせる
		if (!fps_->UpdateFrameRate()) continue;

		// 画面を初期化
		ClearDrawScreen();

		fps_->CalcFrameRate();	// フレームレート計算
		fps_->DrawFrameRate();	// フレームレート描画

		ScreenFlip();
	}
}

// 解放
void Application::Release(void)
{
	// フレームレート解放
	delete fps_;

	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
}
