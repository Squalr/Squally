#include "Beetle.h"

Beetle* Beetle::create()
{
	Beetle* instance = new Beetle();

	instance->autorelease();

	return instance;
}

Beetle::Beetle() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Beetle::~Beetle()
{
}
