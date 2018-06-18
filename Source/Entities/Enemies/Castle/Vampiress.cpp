#include "Vampiress.h"

const std::string Vampiress::KeyEnemyVampiress = "vampiress";

Vampiress* Vampiress::create()
{
	Vampiress* instance = new Vampiress();

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Vampiress_Animations,
	false,
	Size(96.0f, 236.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Vampiress::~Vampiress()
{
}
