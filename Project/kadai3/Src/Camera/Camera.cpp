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
	// �ړ����������߂�
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_UP))	{ moveDir = AsoUtility::DIR_F; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_DOWN))	{ moveDir = AsoUtility::DIR_B; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_LEFT))	{ moveDir = AsoUtility::DIR_L; }
	if (InputManager::GetInstance()->IsNew(KEY_INPUT_RIGHT)){ moveDir = AsoUtility::DIR_R; }

	// �ړ��ʂ��v�Z����(�����~�X�s�[�h)
	VECTOR movePow = VScale(moveDir, MOVE_SPEED);

	// �ړ�����(���W�{�ړ���)
	pos_ = VAdd(pos_, movePow);
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
