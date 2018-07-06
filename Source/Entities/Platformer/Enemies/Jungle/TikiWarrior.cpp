#include "TikiWarrior.h"

const std::string TikiWarrior::KeyEnemyTikiWarrior = "tiki_warrior";

TikiWarrior* TikiWarrior::deserialize(ValueMap* initProperties)
{
	TikiWarrior* instance = new TikiWarrior(initProperties);

	instance->autorelease();

	return instance;
}

TikiWarrior::TikiWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_TikiWarrior_Animations,
	false,
	Size(128.0f, 128.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TikiWarrior::~TikiWarrior()
{
}
