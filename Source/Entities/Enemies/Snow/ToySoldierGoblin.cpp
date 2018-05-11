#include "ToySoldierGoblin.h"

ToySoldierGoblin* ToySoldierGoblin::create()
{
	ToySoldierGoblin* instance = new ToySoldierGoblin();

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_ToySoldierGoblin_Animations,
	false)
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}
