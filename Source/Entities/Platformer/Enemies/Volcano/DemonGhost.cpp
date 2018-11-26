#include "DemonGhost.h"

const std::string DemonGhost::MapKeyEnemyDemonGhost = "demon_ghost";

DemonGhost* DemonGhost::deserialize(ValueMap* initProperties)
{
	DemonGhost* instance = new DemonGhost(initProperties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Volcano_Enemies_DemonGhost_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 320.0f),
	0.7f,
	Vec2(0.0f, 40.0f))
{
}

DemonGhost::~DemonGhost()
{
}
