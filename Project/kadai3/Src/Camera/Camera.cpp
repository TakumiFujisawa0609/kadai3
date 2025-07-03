#include "Camera.h"

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
}

void Camera::SetBeforeDraw(void)
{
	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	// �J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
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
	DrawFormatString(0, 20, 0x000000, "�J�������W�F(%.2f, %.2f, %.2f)", pos_.x, pos_.y, pos_.z);
#endif // _DEBUG
}

void Camera::Release(void)
{
}
