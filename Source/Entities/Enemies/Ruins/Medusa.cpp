#include "Medusa.h"

const std::string Medusa::KeyEnemyMedusa = "medusa";

Medusa* Medusa::deserialize(ValueMap* initProperties)
{
	Medusa* instance = new Medusa(initProperties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Medusa_Animations,
	false,
	Size(224.0f, 304.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Medusa::~Medusa()
{
}
