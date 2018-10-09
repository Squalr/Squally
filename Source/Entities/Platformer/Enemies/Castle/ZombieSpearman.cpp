#include "ZombieSpearman.h"

const std::string ZombieSpearman::KeyEnemyZombieSpearman = "zombie_spearman";

ZombieSpearman* ZombieSpearman::deserialize(ValueMap* initProperties)
{
	ZombieSpearman* instance = new ZombieSpearman(initProperties);

	instance->autorelease();

	return instance;
}

ZombieSpearman::ZombieSpearman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Enemies_ZombieSpearman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(114.0f, 208.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

ZombieSpearman::~ZombieSpearman()
{
}
