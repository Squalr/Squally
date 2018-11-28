#include "Zeus.h"

const std::string Zeus::MapKeyNpcZeus = "zeus";

Zeus* Zeus::deserialize(ValueMap* initProperties)
{
	Zeus* instance = new Zeus(initProperties);

	instance->autorelease();

	return instance;
}

Zeus::Zeus(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Zeus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Zeus::~Zeus()
{
}
