#include "Genie.h"

const std::string Genie::MapKeyEnemyGenie = "genie";

Genie* Genie::deserialize(ValueMap* initProperties)
{
	Genie* instance = new Genie(initProperties);

	instance->autorelease();

	return instance;
}

Genie::Genie(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_Genie_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(512.0f, 1126.0f),
	0.20f,
	Vec2(0.0f, -356.0f))
{
}

Genie::~Genie()
{
}
