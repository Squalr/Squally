#include "Yeti.h"

Yeti* Yeti::create()
{
	Yeti* instance = new Yeti();

	instance->autorelease();

	return instance;
}

Yeti::Yeti() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_Yeti_Animations,
	false,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, -280.0f))
{
}

Yeti::~Yeti()
{
}
