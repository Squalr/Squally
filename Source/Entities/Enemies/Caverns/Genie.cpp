#include "Genie.h"

Genie* Genie::create()
{
	Genie* instance = new Genie();

	instance->autorelease();

	return instance;
}

Genie::Genie() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_Genie_Animations,
	false,
	Size(1024.0f, 960.0f),
	0.20f,
	Vec2(0.0f, -480.0f))
{
}

Genie::~Genie()
{
}
