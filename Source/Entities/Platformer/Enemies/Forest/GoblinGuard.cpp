#include "GoblinGuard.h"

const std::string GoblinGuard::KeyEnemyGoblinGuard = "goblin_guard";

GoblinGuard* GoblinGuard::deserialize(ValueMap* initProperties)
{
	GoblinGuard* instance = new GoblinGuard(initProperties);

	instance->autorelease();

	return instance;
}

GoblinGuard::GoblinGuard(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_GoblinGuard_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 768.0f),
	0.3f,
	Vec2(-24.0f, -368.0f))
{
}

GoblinGuard::~GoblinGuard()
{
}
