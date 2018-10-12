#include "Shade.h"

const std::string Shade::MapKeyEnemyShade = "shade";

Shade* Shade::deserialize(ValueMap* initProperties)
{
	Shade* instance = new Shade(initProperties);

	instance->autorelease();

	return instance;
}

Shade::Shade(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Enemies_Shade_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, -128.0f))
{
}

Shade::~Shade()
{
}
