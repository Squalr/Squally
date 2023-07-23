#include "Bat.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bat::MapKey = "bat";

Bat* Bat::deserialize(ValueMap& properties)
{
	Bat* instance = new Bat(properties);

	instance->autorelease();

	return instance;
}

Bat::Bat(ValueMap& properties) : super(properties,
	Bat::MapKey,
	EntityResources::Misc_CastleValgrind_Bat_Animations,
	EntityResources::Misc_CastleValgrind_Bat_Emblem,
	CSize(192.0f, 160.0f),
	1.0f)
{
}

Bat::~Bat()
{
}

Vec2 Bat::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bat::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Bat::create();
}
