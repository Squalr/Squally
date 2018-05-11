#include "Minotaur.h"

Minotaur* Minotaur::create()
{
	Minotaur* instance = new Minotaur();

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_Minotaur_Animations,
	false)
{
}

Minotaur::~Minotaur()
{
}
