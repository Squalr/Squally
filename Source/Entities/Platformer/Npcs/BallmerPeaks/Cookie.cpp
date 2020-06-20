#include "Cookie.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cookie::MapKey = "cookie";

Cookie* Cookie::deserialize(ValueMap& properties)
{
	Cookie* instance = new Cookie(properties);

	instance->autorelease();

	return instance;
}

Cookie::Cookie(ValueMap& properties) : super(properties,
	Cookie::MapKey,
	EntityResources::Npcs_BallmerPeaks_Cookie_Animations,
	EntityResources::Npcs_BallmerPeaks_Cookie_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Cookie::~Cookie()
{
}

Vec2 Cookie::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cookie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BallmerPeaks_Cookie::create();
}
