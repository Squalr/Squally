#include "LionMan.h"

const std::string LionMan::KeyEnemyLionMan = "lion_man";

LionMan* LionMan::create()
{
	LionMan* instance = new LionMan();

	instance->autorelease();

	return instance;
}

LionMan::LionMan() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_LionMan_Animations,
	false,
	Size(256.0f, 326.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

LionMan::~LionMan()
{
}
