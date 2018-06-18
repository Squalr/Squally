#include "DemonWarrior.h"

const std::string DemonWarrior::KeyEnemyDemonWarrior = "demon_warrior";

DemonWarrior* DemonWarrior::create()
{
	DemonWarrior* instance = new DemonWarrior();

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonWarrior_Animations,
	false,
	Size(320.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonWarrior::~DemonWarrior()
{
}
