#include "Hunter.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Hunter::MapKey = "hunter";

Hunter* Hunter::deserialize(ValueMap& properties)
{
	Hunter* instance = new Hunter(properties);

	instance->autorelease();

	return instance;
}

Hunter::Hunter(ValueMap& properties) : super(properties,
	Hunter::MapKey,
	EntityResources::Enemies_LambdaCrypts_Hunter_Animations,
	EntityResources::Enemies_LambdaCrypts_Hunter_Emblem,
	Size(112.0f, 596.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Hunter::~Hunter()
{
}

Vec2 Hunter::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Hunter::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Hunter::create();
}
