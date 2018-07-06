#include "Executioner.h"

const std::string Executioner::KeyEnemyExecutioner = "executioner";

Executioner* Executioner::deserialize(ValueMap* initProperties)
{
	Executioner* instance = new Executioner(initProperties);

	instance->autorelease();

	return instance;
}

Executioner::Executioner(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Executioner_Animations,
	false,
	Size(472.0f, 820.0f),
	0.3f,
	Vec2(-24.0f, -410.0f))
{
}

Executioner::~Executioner()
{
}
