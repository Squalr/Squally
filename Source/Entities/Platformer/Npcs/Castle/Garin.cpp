#include "Garin.h"

const std::string Garin::MapKeyNpcGarin = "garin";

Garin* Garin::deserialize(ValueMap* initProperties)
{
	Garin* instance = new Garin(initProperties);

	instance->autorelease();

	return instance;
}

Garin::Garin(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_Garin_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Garin::~Garin()
{
}
