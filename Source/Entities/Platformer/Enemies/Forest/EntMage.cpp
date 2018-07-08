#include "EntMage.h"

const std::string EntMage::KeyEnemyEntMage = "ent_mage";

EntMage* EntMage::deserialize(ValueMap* initProperties)
{
	EntMage* instance = new EntMage(initProperties);

	instance->autorelease();

	return instance;
}

EntMage::EntMage(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_EntMage_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(512.0f, 820.0f),
	0.3f,
	Vec2(24.0f, -410.0f))
{
}

EntMage::~EntMage()
{
}
