#include "DemonRogue.h"

const std::string DemonRogue::KeyEnemyDemonRogue = "demon_rogue";

DemonRogue* DemonRogue::deserialize(ValueMap* initProperties)
{
	DemonRogue* instance = new DemonRogue(initProperties);

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Enemies_DemonRogue_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonRogue::~DemonRogue()
{
}
