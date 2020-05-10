#include "Knight.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Knight::MapKey = "knight";

Knight* Knight::deserialize(ValueMap& properties)
{
	Knight* instance = new Knight(properties);

	instance->autorelease();

	return instance;
}

Knight::Knight(ValueMap& properties) : super(properties,
	Knight::MapKey,
	EntityResources::Helpers_CastleValgrind_Knight_Animations,
	EntityResources::Helpers_CastleValgrind_Knight_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Knight::~Knight()
{
}

Vec2 Knight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Knight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Knight::create();
}
