#include "Tinsel.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tinsel::MapKey = "tinsel";

Tinsel* Tinsel::deserialize(ValueMap& properties)
{
	Tinsel* instance = new Tinsel(properties);

	instance->autorelease();

	return instance;
}

Tinsel::Tinsel(ValueMap& properties) : super(properties,
	Tinsel::MapKey,
	EntityResources::Npcs_BalmerPeaks_Tinsel_Animations,
	EntityResources::Npcs_BalmerPeaks_Tinsel_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Tinsel::~Tinsel()
{
}

Vec2 Tinsel::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Tinsel::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Tinsel::create();
}
