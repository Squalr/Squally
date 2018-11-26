#include "Yeti.h"

const std::string Yeti::MapKeyEnemyYeti = "yeti";

Yeti* Yeti::deserialize(ValueMap* initProperties)
{
	Yeti* instance = new Yeti(initProperties);

	instance->autorelease();

	return instance;
}

Yeti::Yeti(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Snow_Enemies_Yeti_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, -280.0f))
{
}

Yeti::~Yeti()
{
}
