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
	Size(256.0f, 512.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Yeti::~Yeti()
{
}
