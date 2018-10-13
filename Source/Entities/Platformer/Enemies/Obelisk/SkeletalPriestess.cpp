#include "SkeletalPriestess.h"

const std::string SkeletalPriestess::MapKeyEnemySkeletalPriestess = "skeletal_priestess";

SkeletalPriestess* SkeletalPriestess::deserialize(ValueMap* initProperties)
{
	SkeletalPriestess* instance = new SkeletalPriestess(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalPriestess::SkeletalPriestess(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalPriestess_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalPriestess::~SkeletalPriestess()
{
}
