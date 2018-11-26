#include "Viper.h"

const std::string Viper::MapKeyNpcViper = "viper";

Viper* Viper::deserialize(ValueMap* initProperties)
{
	Viper* instance = new Viper(initProperties);

	instance->autorelease();

	return instance;
}

Viper::Viper(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Npcs_Viper_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Viper::~Viper()
{
}
