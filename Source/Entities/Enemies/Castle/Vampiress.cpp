#include "Vampiress.h"

Vampiress* Vampiress::create()
{
	Vampiress* instance = new Vampiress();

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Vampiress_Animations,
	false)
{
}

Vampiress::~Vampiress()
{
}
