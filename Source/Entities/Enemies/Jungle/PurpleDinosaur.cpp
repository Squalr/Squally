#include "PurpleDinosaur.h"

PurpleDinosaur* PurpleDinosaur::create()
{
	PurpleDinosaur* instance = new PurpleDinosaur();

	instance->autorelease();

	return instance;
}

PurpleDinosaur::PurpleDinosaur() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_PurpleDinosaur_Animations,
	false,
	Size(396.0f, 324.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

PurpleDinosaur::~PurpleDinosaur()
{
}
