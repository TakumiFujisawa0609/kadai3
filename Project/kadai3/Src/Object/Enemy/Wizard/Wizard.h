#pragma once
#include "../EnemyBase.h"

class Wizard : public EnemyBase
{
public:
	// �U���Ԋu(1�b = 60fps)
	static constexpr int ATTACK_INTERVAL = 120;

public:
	Wizard(void);			// �R���X�g���N�^
	virtual ~Wizard(void);	// �f�X�g���N�^

protected:
	// �p�����[�^�̐ݒ�
	void SetParam(void) override;

	// ��ԕʍX�V
	void UpdateMoving(void) override;
};