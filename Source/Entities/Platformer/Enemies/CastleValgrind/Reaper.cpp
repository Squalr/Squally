#include "Reaper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Reaper::MapKey = "reaper";

Reaper* Reaper::deserialize(ValueMap& properties)
{
	Reaper* instance = new Reaper(properties);

	instance->autorelease();

	return instance;
}

Reaper::Reaper(ValueMap& properties) : super(properties,
	Reaper::MapKey,
	EntityResources::Enemies_CastleValgrind_Reaper_Animations,
	EntityResources::Enemies_CastleValgrind_Reaper_Emblem,
	Size(196.0f, 512.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Reaper::~Reaper()
{
}

Vec2 Reaper::getDialogueOffset()
{
	return Vec2(-16.0f, -288.0f);
}

LocalizedString* Reaper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Reaper::create();
}
