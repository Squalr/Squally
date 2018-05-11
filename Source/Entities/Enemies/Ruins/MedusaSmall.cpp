#include "MedusaSmall.h"

MedusaSmall* MedusaSmall::create()
{
	MedusaSmall* instance = new MedusaSmall();

	instance->autorelease();

	return instance;
}

MedusaSmall::MedusaSmall() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_MedusaSmall_Animations,
	false)
{
}

MedusaSmall::~MedusaSmall()
{
}
