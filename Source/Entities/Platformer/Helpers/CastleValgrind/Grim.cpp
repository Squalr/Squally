#include "Grim.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Grim::MapKey = "grim";

Grim* Grim::deserialize(ValueMap& properties)
{
	Grim* instance = new Grim(properties);

	instance->autorelease();

	return instance;
}

Grim::Grim(ValueMap& properties) : super(properties,
	Grim::MapKey,
	EntityResources::Helpers_CastleValgrind_Grim_Animations,
	EntityResources::Helpers_CastleValgrind_Grim_Emblem,
	CSize(224.0f, 440.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Grim::~Grim()
{
}

Vec2 Grim::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Grim::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create();
}
