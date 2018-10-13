#include "EvilEye.h"

const std::string EvilEye::MapKeyEnemyEvilEye = "evil_eye";

EvilEye* EvilEye::deserialize(ValueMap* initProperties)
{
	EvilEye* instance = new EvilEye(initProperties);

	instance->autorelease();

	return instance;
}

EvilEye::EvilEye(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Enemies_EvilEye_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(720.0f, 840.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

EvilEye::~EvilEye()
{
}
