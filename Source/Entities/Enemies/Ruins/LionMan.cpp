#include "LionMan.h"

LionMan* LionMan::create()
{
	LionMan* instance = new LionMan();

	instance->autorelease();

	return instance;
}

LionMan::LionMan() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_LionMan_Animations,
	false)
{
}

LionMan::~LionMan()
{
}
