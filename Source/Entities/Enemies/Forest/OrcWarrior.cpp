#include "OrcWarrior.h"

const std::string OrcWarrior::KeyEnemyOrcWarrior = "orc_warrior";

OrcWarrior* OrcWarrior::create()
{
	OrcWarrior* instance = new OrcWarrior();

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_OrcWarrior_Animations,
	false,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcWarrior::~OrcWarrior()
{
}
