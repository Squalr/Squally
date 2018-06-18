#include "TikiWarrior.h"

const std::string TikiWarrior::KeyEnemyTikiWarrior = "tiki_warrior";

TikiWarrior* TikiWarrior::create()
{
	TikiWarrior* instance = new TikiWarrior();

	instance->autorelease();

	return instance;
}

TikiWarrior::TikiWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_TikiWarrior_Animations,
	false,
	Size(128.0f, 128.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TikiWarrior::~TikiWarrior()
{
}
