#include "Shen.h"

const std::string Shen::MapKeyNpcShen = "shen";

Shen* Shen::deserialize(ValueMap* initProperties)
{
	Shen* instance = new Shen(initProperties);

	instance->autorelease();

	return instance;
}

Shen::Shen(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Shen_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Shen::~Shen()
{
}
