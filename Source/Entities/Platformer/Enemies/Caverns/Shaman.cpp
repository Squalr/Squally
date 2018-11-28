#include "Shaman.h"

const std::string Shaman::MapKeyEnemyShaman = "shaman";

Shaman* Shaman::deserialize(ValueMap* initProperties)
{
	Shaman* instance = new Shaman(initProperties);

	instance->autorelease();

	return instance;
}

Shaman::Shaman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_Shaman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 288.0f),
	0.75f,
	Vec2(0.0f, 0.0f))
{
}

Shaman::~Shaman()
{
}
