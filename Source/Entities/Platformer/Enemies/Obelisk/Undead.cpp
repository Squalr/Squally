#include "Undead.h"

const std::string Undead::MapKeyEnemyUndead = "undead";

Undead* Undead::deserialize(ValueMap* initProperties)
{
	Undead* instance = new Undead(initProperties);

	instance->autorelease();

	return instance;
}

Undead::Undead(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Enemies_Undead_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(146.0f, 248.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Undead::~Undead()
{
}
