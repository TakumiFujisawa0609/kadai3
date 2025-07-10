#pragma once
#include <DxLib.h>

class Camera
{
public:
	// シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Camera(); } };
	static Camera* GetInstance(void) { return instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

private:
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	Camera();
	~Camera();

	// 静的インスタンス
	static Camera* instance_;

public:

	// カメラの初期位置
	static constexpr VECTOR INIT_POS = { 0.0f, 1000.0f, -1000.0f };

	// カメラの初期角度
	static constexpr VECTOR INIT_ANGLE = { 30.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };

	// カメラクリップ：NEAR
	static constexpr float CAMERA_NEAR = 3.0f;

	// カメラクリップ：FAR
	static constexpr float CAMERA_FAR = 5000.0f;

	// カメラスピード(移動)
	static constexpr float MOVE_SPEED = 10.0f;

	// カメラスピード(度)
	static constexpr float ANGLE_SPEED = 1.0f;

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void DrawDebug(void);
	void Release(void);

	// 追従する座標
	void SetFollowPos(VECTOR pos);

private:

	// カメラの追従対象の位置
	VECTOR followPos_;

	// カメラの位置
	VECTOR pos_;

	// カメラ角度(rad)
	VECTOR angle_;

};