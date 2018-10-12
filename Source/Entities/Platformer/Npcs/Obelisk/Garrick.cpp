#include "Garrick.h"

const std::string Garrick::MapKeyNpcGarrick = "garrick";

Garrick* Garrick::deserialize(ValueMap* initProperties)
{
	Garrick* instance = new Garrick(initProperties);

	instance->autorelease();

	return instance;
}

Garrick::Garrick(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Garrick_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Garrick::~Garrick()
{
}
