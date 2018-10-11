#include "Asmodeus.h"

const std::string Asmodeus::KeyEnemyAsmodeus = "asmodeus";

Asmodeus* Asmodeus::deserialize(ValueMap* initProperties)
{
	Asmodeus* instance = new Asmodeus(initProperties);

	instance->autorelease();

	return instance;
}

Asmodeus::Asmodeus(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Enemies_Asmodeus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(480.0f, 480.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

Asmodeus::~Asmodeus()
{
}
