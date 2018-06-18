#include "Vampiress.h"

const std::string Vampiress::KeyEnemyVampiress = "vampiress";

Vampiress* Vampiress::deserialize(ValueMap* initProperties)
{
	Vampiress* instance = new Vampiress(initProperties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(ValueMap* initProperties) : Enemy(initProperties,
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
