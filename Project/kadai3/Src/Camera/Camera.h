#pragma once
#include <DxLib.h>

class Camera
{

public:

	// �J�����̏����ʒu
	static constexpr VECTOR INIT_POS = { 0.0f, 1000.0f, -1000.0f };

	// �J�����̏����p�x
	static constexpr VECTOR INIT_ANGLE = { 30.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };

	// �J�����N���b�v�FNEAR
	static constexpr float CAMERA_NEAR = 3.0f;

	// �J�����N���b�v�FFAR
	static constexpr float CAMERA_FAR = 5000.0f;

	// �J�����X�s�[�h(�ړ�)
	static constexpr float MOVE_SPEED = 10.0f;

	// �J�����X�s�[�h(�x)
	static constexpr float ANGLE_SPEED = 1.0f;

	Camera(void);
	~Camera(void);

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void DrawDebug(void);
	void Release(void);

private:

	// �J�����̈ʒu
	VECTOR pos_;

	// �J�����p�x(rad)
	VECTOR angle_;

};