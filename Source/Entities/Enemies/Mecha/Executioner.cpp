#include "Executioner.h"

Executioner* Executioner::create()
{
	Executioner* instance = new Executioner();

	instance->autorelease();

	return instance;
}

Executioner::Executioner() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Executioner::~Executioner()
{
}
