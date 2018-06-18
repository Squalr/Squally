#include "AnubisWarrior.h"

const std::string AnubisWarrior::KeyEnemyAnubisWarrior = "anubis_warrior";

AnubisWarrior* AnubisWarrior::deserialize(ValueMap* initProperties)
{
	AnubisWarrior* instance = new AnubisWarrior(initProperties);

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Ruins_AnubisWarrior_Animations,
	false,
	Size(256.0f, 292.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

AnubisWarrior::~AnubisWarrior()
{
}
