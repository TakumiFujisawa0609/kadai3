#include "Camera.h"
#include "../Input/InputManager.h"
#include "../Utility/AsoUtility.h"

Camera::Camera(void)
{
}
Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	pos_ = INIT_POS;
	angle_ = INIT_ANGLE;
}

void Camera::Update(void)
{
	// 移動方向を決める
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_I)){ moveDir = AsoUtility::DIR_F; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_K)){ moveDir = AsoUtility::DIR_B; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_J)){ moveDir = AsoUtility::DIR_L; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_L)){ moveDir = AsoUtility::DIR_R; }

	// 移動量を計算する(方向×スピード)
	VECTOR movePow = VScale(moveDir, MOVE_SPEED);

	// 移動処理(座標＋移動量)
	pos_ = VAdd(pos_, movePow);
	
	// X軸の角度調整
	float anglePowRad = AsoUtility::Deg2RadF(ANGLE_SPEED);
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_U)) { angle_.x += anglePowRad; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_O)) { angle_.x -= anglePowRad; }

}

void Camera::SetBeforeDraw(void)
{
	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angle_.x,
		angle_.y,
		angle_.z
	);
}

void Camera::DrawDebug(void)
{
#ifdef _DEBUG
	DrawFormatString(0, 20, 0x000000, "カメラ座標：(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
#endif // _DEBUG
}

void Camera::Release(void)
{
}
