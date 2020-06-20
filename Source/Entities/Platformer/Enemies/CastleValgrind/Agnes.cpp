#include "Agnes.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Agnes::MapKey = "agnes";

Agnes* Agnes::deserialize(ValueMap& properties)
{
	Agnes* instance = new Agnes(properties);

	instance->autorelease();

	return instance;
}

Agnes::Agnes(ValueMap& properties) : super(properties,
	Agnes::MapKey,
	EntityResources::Enemies_CastleValgrind_Agnes_Animations,
	EntityResources::Enemies_CastleValgrind_Agnes_Emblem,
	Size(360.0f, 420.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Agnes::~Agnes()
{
}

Vec2 Agnes::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Agnes::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Agnes::create();
}
