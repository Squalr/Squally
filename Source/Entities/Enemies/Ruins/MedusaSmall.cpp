#include "MedusaSmall.h"

MedusaSmall* MedusaSmall::create()
{
	MedusaSmall* instance = new MedusaSmall();

	instance->autorelease();

	return instance;
}

MedusaSmall::MedusaSmall() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_MedusaSmall_Animations,
	false,
	Size(224.0f, 288.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

MedusaSmall::~MedusaSmall()
{
}
