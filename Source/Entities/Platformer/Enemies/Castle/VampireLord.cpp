#include "VampireLord.h"

const std::string VampireLord::MapKeyEnemyVampireLord = "vampire_lord";

VampireLord* VampireLord::deserialize(ValueMap* initProperties)
{
	VampireLord* instance = new VampireLord(initProperties);

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Castle_Enemies_VampireLord_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

VampireLord::~VampireLord()
{
}
