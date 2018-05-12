#include "ToySoldierGoblin.h"

ToySoldierGoblin* ToySoldierGoblin::create()
{
	ToySoldierGoblin* instance = new ToySoldierGoblin();

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_ToySoldierGoblin_Animations,
	false,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}
