#include "AnubisTiny.h"

const std::string AnubisTiny::KeyEnemyAnubisTiny = "anubis_tiny";

AnubisTiny* AnubisTiny::deserialize(ValueMap* initProperties)
{
	AnubisTiny* instance = new AnubisTiny(initProperties);

	instance->autorelease();

	return instance;
}

AnubisTiny::AnubisTiny(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_AnubisTiny_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 186.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

AnubisTiny::~AnubisTiny()
{
}
