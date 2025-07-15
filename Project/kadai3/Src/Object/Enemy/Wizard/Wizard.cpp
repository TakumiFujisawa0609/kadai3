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
