#include "AnubisTiny.h"

AnubisTiny* AnubisTiny::create()
{
	AnubisTiny* instance = new AnubisTiny();

	instance->autorelease();

	return instance;
}

AnubisTiny::AnubisTiny() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_AnubisTiny_Animations,
	false)
{
}

AnubisTiny::~AnubisTiny()
{
}
