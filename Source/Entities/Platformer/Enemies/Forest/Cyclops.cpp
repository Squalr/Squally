#include "Cyclops.h"

const std::string Cyclops::KeyEnemyCyclops = "cyclops";

Cyclops* Cyclops::deserialize(ValueMap* initProperties)
{
	Cyclops* instance = new Cyclops(initProperties);

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Enemies_Cyclops_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Cyclops::~Cyclops()
{
}
