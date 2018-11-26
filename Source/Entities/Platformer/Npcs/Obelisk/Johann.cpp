#include "Johann.h"

const std::string Johann::MapKeyNpcJohann = "johann";

Johann* Johann::deserialize(ValueMap* initProperties)
{
	Johann* instance = new Johann(initProperties);

	instance->autorelease();

	return instance;
}

Johann::Johann(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Npcs_Johann_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Johann::~Johann()
{
}
