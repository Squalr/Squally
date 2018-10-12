#include "Wraith.h"

const std::string Wraith::MapKeyEnemyWraith = "wraith";

Wraith* Wraith::deserialize(ValueMap* initProperties)
{
	Wraith* instance = new Wraith(initProperties);

	instance->autorelease();

	return instance;
}

Wraith::Wraith(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Enemies_Wraith_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(142.0f, 400.0f),
	0.5f,
	Vec2(0.0f, 40.0f))
{
}

Wraith::~Wraith()
{
}
