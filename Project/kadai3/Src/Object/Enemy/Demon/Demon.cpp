#include "Demon.h"

Demon::Demon(void)
{
}

Demon::~Demon(void)
{
}

void Demon::SetParam(void)
{
	hp_ = 2;
	collRadius_ = 50.0f;
	spawnRange_ = 1.0f;
	scale_ = { 0.5f,0.5f,0.5f };
	speed_ = 5.0f;
}
