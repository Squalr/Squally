#include "Fraya.h"

const std::string Fraya::KeyEnemyFraya = "fraya";

Fraya* Fraya::deserialize(ValueMap* initProperties)
{
	Fraya* instance = new Fraya(initProperties);

	instance->autorelease();

	return instance;
}

Fraya::Fraya(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Fraya_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Fraya::~Fraya()
{
}
