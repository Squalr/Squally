#include "AnubisPup.h"

const std::string AnubisPup::KeyEnemyAnubisPup = "anubis_pup";

AnubisPup* AnubisPup::deserialize(ValueMap* initProperties)
{
	AnubisPup* instance = new AnubisPup(initProperties);

	instance->autorelease();

	return instance;
}

AnubisPup::AnubisPup(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_AnubisPup_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 186.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

AnubisPup::~AnubisPup()
{
}
