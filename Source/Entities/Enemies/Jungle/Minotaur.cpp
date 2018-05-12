#include "Minotaur.h"

Minotaur* Minotaur::create()
{
	Minotaur* instance = new Minotaur();

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_Minotaur_Animations,
	false,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, -124.0f))
{
}

Minotaur::~Minotaur()
{
}
