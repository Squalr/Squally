#include "Mantis.h"

Mantis* Mantis::create()
{
	Mantis* instance = new Mantis();

	instance->autorelease();

	return instance;
}

Mantis::Mantis() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_Mantis_Animations,
	false)
{
}

Mantis::~Mantis()
{
}
