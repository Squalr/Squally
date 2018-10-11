#include "PenguinWarrior.h"

const std::string PenguinWarrior::KeyEnemyPenguinWarrior = "penguin_warrior";

PenguinWarrior* PenguinWarrior::deserialize(ValueMap* initProperties)
{
	PenguinWarrior* instance = new PenguinWarrior(initProperties);

	instance->autorelease();

	return instance;
}

PenguinWarrior::PenguinWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_Enemies_PenguinWarrior_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 296.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

PenguinWarrior::~PenguinWarrior()
{
}
