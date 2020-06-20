#include "Viper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Viper::MapKey = "viper";

Viper* Viper::deserialize(ValueMap& properties)
{
	Viper* instance = new Viper(properties);

	instance->autorelease();

	return instance;
}

Viper::Viper(ValueMap& properties) : super(properties,
	Viper::MapKey,
	EntityResources::Npcs_LambdaCrypts_Viper_Animations,
	EntityResources::Npcs_LambdaCrypts_Viper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Viper::~Viper()
{
}

Vec2 Viper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Viper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Viper::create();
}
