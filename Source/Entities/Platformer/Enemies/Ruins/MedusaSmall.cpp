#include "MedusaSmall.h"

const std::string MedusaSmall::KeyEnemyMedusaSmall = "medusa_small";

MedusaSmall* MedusaSmall::deserialize(ValueMap* initProperties)
{
	MedusaSmall* instance = new MedusaSmall(initProperties);

	instance->autorelease();

	return instance;
}

MedusaSmall::MedusaSmall(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_MedusaSmall_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(224.0f, 288.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

MedusaSmall::~MedusaSmall()
{
}
