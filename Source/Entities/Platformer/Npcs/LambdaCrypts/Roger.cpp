#include "Roger.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Roger::MapKey = "roger";

Roger* Roger::deserialize(ValueMap& properties)
{
	Roger* instance = new Roger(properties);

	instance->autorelease();

	return instance;
}

Roger::Roger(ValueMap& properties) : super(properties,
	Roger::MapKey,
	EntityResources::Npcs_LambdaCrypts_Roger_Animations,
	EntityResources::Npcs_LambdaCrypts_Roger_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Roger::~Roger()
{
}

Vec2 Roger::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Roger::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Roger::create();
}
