#include "Lycan.h"

const std::string Lycan::MapKeyNpcLycan = "lycan";

Lycan* Lycan::deserialize(ValueMap* initProperties)
{
	Lycan* instance = new Lycan(initProperties);

	instance->autorelease();

	return instance;
}

Lycan::Lycan(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Forest_Npcs_Lycan_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Lycan::~Lycan()
{
}
