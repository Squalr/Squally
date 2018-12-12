#include "VoidArcher.h"

const std::string VoidArcher::MapKeyEnemyVoidArcher = "void_archer";

VoidArcher* VoidArcher::deserialize(ValueMap* initProperties)
{
	VoidArcher* instance = new VoidArcher(initProperties);

	instance->autorelease();

	return instance;
}

VoidArcher::VoidArcher(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Obelisk_Enemies_VoidArcher_Animations,
	PlatformerCollisionType::Enemy,
	Size(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

VoidArcher::~VoidArcher()
{
}
