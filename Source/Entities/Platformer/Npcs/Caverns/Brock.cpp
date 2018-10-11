#include "Brock.h"

const std::string Brock::KeyEnemyBrock = "brock";

Brock* Brock::deserialize(ValueMap* initProperties)
{
	Brock* instance = new Brock(initProperties);

	instance->autorelease();

	return instance;
}

Brock::Brock(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Brock_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Brock::~Brock()
{
}
