#include "Minotaur.h"

Minotaur* Minotaur::create()
{
	Minotaur* instance = new Minotaur();

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Minotaur::~Minotaur()
{
}
