#pragma once
#include "BulletBase.h"

class Straight : public BulletBase
{

public:

	// �R���X�g���N�^(���ƂȂ郂�f���̃n���h��ID)
	Straight(void);

	// �f�X�g���N�^
	virtual ~Straight(void);

private:

	// �p�����[�^�ݒ�
	void SetParam(void) override;

};
