#include "FrostShooter.h"

const std::string FrostShooter::KeyEnemyFrostShooter = "frost_shooter";

FrostShooter* FrostShooter::deserialize(ValueMap* initProperties)
{
	FrostShooter* instance = new FrostShooter(initProperties);

	instance->autorelease();

	return instance;
}

FrostShooter::FrostShooter(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_FrostShooter_Animations,
	false,
	Size(212.0f, 296.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

FrostShooter::~FrostShooter()
{
}
