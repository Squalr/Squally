#include "Medusa.h"

Medusa* Medusa::create()
{
	Medusa* instance = new Medusa();

	instance->autorelease();

	return instance;
}

Medusa::Medusa() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Medusa::~Medusa()
{
}
