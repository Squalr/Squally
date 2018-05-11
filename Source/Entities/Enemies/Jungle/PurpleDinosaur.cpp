#include "PurpleDinosaur.h"

PurpleDinosaur* PurpleDinosaur::create()
{
	PurpleDinosaur* instance = new PurpleDinosaur();

	instance->autorelease();

	return instance;
}

PurpleDinosaur::PurpleDinosaur() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_PurpleDinosaur_Animations,
	false)
{
}

PurpleDinosaur::~PurpleDinosaur()
{
}
