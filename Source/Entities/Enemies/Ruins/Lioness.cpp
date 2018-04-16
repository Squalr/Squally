#include "Lioness.h"

Lioness* Lioness::create()
{
	Lioness* instance = new Lioness();

	instance->autorelease();

	return instance;
}

Lioness::Lioness() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Lioness::~Lioness()
{
}
