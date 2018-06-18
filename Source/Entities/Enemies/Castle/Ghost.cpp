#include "Ghost.h"

const std::string Ghost::KeyEnemyGhost = "ghost";

Ghost* Ghost::create()
{
	Ghost* instance = new Ghost();

	instance->autorelease();

	return instance;
}

Ghost::Ghost() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Ghost_Animations,
	false,
	Size(480.0f, 692.0f),
	0.3f,
	Vec2(-32.0f, -224.0f))
{
}

Ghost::~Ghost()
{
}
