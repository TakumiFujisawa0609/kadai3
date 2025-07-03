#pragma once
#include <DxLib.h>

class Camera
{

public:

	// カメラの初期位置
	static constexpr VECTOR INIT_POS = { 0.0f, 1000.0f, -1000.0f };

	// カメラの初期角度
	static constexpr VECTOR INIT_ANGLE = { 30.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };

	// カメラクリップ：NEAR
	static constexpr float CAMERA_NEAR = 3.0f;

	// カメラクリップ：FAR
	static constexpr float CAMERA_FAR = 5000.0f;

	Camera(void);
	~Camera(void);

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void DrawDebug(void);
	void Release(void);

private:

	// カメラの位置
	VECTOR pos_;

	// カメラ角度(rad)
	VECTOR angle_;

};