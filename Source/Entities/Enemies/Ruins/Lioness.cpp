#include "Lioness.h"

const std::string Lioness::KeyEnemyLioness = "lioness";

Lioness* Lioness::create()
{
	Lioness* instance = new Lioness();

	instance->autorelease();

	return instance;
}

Lioness::Lioness() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Lioness_Animations,
	false,
	Size(128.0f, 278.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Lioness::~Lioness()
{
}
