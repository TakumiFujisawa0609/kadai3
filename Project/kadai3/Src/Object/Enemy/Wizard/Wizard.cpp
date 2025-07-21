#include "Wizard.h"

Wizard::Wizard(void)
{
}

Wizard::~Wizard(void)
{
}

void Wizard::SetParam(void)
{
	hp_ = 1;
	collRadius_ = 50.0f;
	spawnRange_ = 0.8f;
	scale_ = { 0.5f, 0.5f, 0.5f };
	speed_ = 0.0f;
}

void Wizard::UpdateMoving(void)
{
	// �v���C���[�̕���������
	LookPlayer();

	// �U���J�E���^�̉��Z
	attackCount_++;

	// �J�E���^���U����ԂɂȂ�����
	if (attackCount_ > ATTACK_INTERVAL)
	{
		// �J�E���^�̏�����
		attackCount_ = 0;

		// �U����Ԃ�
		ChangeState(STATE::ATTACK);
	}
}
