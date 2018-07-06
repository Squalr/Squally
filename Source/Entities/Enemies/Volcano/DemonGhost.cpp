#include "DemonGhost.h"

const std::string DemonGhost::KeyEnemyDemonGhost = "demon_ghost";

DemonGhost* DemonGhost::deserialize(ValueMap* initProperties)
{
	DemonGhost* instance = new DemonGhost(initProperties);

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_DemonGhost_Animations,
	false,
	Size(256.0f, 320.0f),
	0.7f,
	Vec2(0.0f, 40.0f))
{
}

DemonGhost::~DemonGhost()
{
}
