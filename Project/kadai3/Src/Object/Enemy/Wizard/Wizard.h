#pragma once
#include "../EnemyBase.h"

class Wizard : public EnemyBase
{
public:
	Wizard(void);			// �R���X�g���N�^
	virtual ~Wizard(void);	// �f�X�g���N�^

protected:
	// �p�����[�^�̐ݒ�
	void SetParam(void) override;

};