#include "GoblinWarrior.h"

const std::string GoblinWarrior::KeyEnemyGoblinWarrior = "goblin_warrior";

GoblinWarrior* GoblinWarrior::deserialize(ValueMap* initProperties)
{
	GoblinWarrior* instance = new GoblinWarrior(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarrior::GoblinWarrior(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_GoblinWarrior_Animations,
	false,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinWarrior::~GoblinWarrior()
{
}
