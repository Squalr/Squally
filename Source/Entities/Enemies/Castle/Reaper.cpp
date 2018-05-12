#include "Reaper.h"

Reaper* Reaper::create()
{
	Reaper* instance = new Reaper();

	instance->autorelease();

	return instance;
}

Reaper::Reaper() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Reaper_Animations,
	false,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, -128.0f))
{
}

Reaper::~Reaper()
{
}
