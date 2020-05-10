#include "Gecko.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gecko::MapKey = "gecko";

Gecko* Gecko::deserialize(ValueMap& properties)
{
	Gecko* instance = new Gecko(properties);

	instance->autorelease();

	return instance;
}

Gecko::Gecko(ValueMap& properties) : super(properties,
	Gecko::MapKey,
	EntityResources::Helpers_SeaSharpCaverns_Gecko_Animations,
	EntityResources::Helpers_SeaSharpCaverns_Gecko_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Gecko::~Gecko()
{
}

Vec2 Gecko::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gecko::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_SeaSharpCaverns_Gecko::create();
}
