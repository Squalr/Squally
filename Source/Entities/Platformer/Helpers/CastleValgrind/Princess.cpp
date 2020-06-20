#include "Princess.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Princess::MapKey = "princess";

Princess* Princess::deserialize(ValueMap& properties)
{
	Princess* instance = new Princess(properties);

	instance->autorelease();

	return instance;
}

Princess::Princess(ValueMap& properties) : super(properties,
	Princess::MapKey,
	EntityResources::Helpers_CastleValgrind_Princess_Animations,
	EntityResources::Helpers_CastleValgrind_Princess_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Princess::~Princess()
{
}

Vec2 Princess::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Princess::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Princess::create();
}
