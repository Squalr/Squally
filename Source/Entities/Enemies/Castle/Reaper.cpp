#include "Reaper.h"

Reaper* Reaper::create()
{
	Reaper* instance = new Reaper();

	instance->autorelease();

	return instance;
}

Reaper::Reaper() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Reaper_Animations,
	false)
{
}

Reaper::~Reaper()
{
}
