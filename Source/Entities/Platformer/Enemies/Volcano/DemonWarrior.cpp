#include "DemonWarrior.h"

const std::string DemonWarrior::KeyEnemyDemonWarrior = "demon_warrior";

DemonWarrior* DemonWarrior::deserialize(ValueMap* initProperties)
{
	DemonWarrior* instance = new DemonWarrior(initProperties);

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_DemonWarrior_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(320.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonWarrior::~DemonWarrior()
{
}
