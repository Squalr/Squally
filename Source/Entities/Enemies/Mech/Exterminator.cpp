#include "Exterminator.h"

Exterminator* Exterminator::create()
{
	Exterminator* instance = new Exterminator();

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_Exterminator_Animations,
	false)
{
}

Exterminator::~Exterminator()
{
}
