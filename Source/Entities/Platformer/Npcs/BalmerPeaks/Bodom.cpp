#include "Bodom.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bodom::MapKey = "bodom";

Bodom* Bodom::deserialize(ValueMap& properties)
{
	Bodom* instance = new Bodom(properties);

	instance->autorelease();

	return instance;
}

Bodom::Bodom(ValueMap& properties) : super(properties,
	Bodom::MapKey,
	EntityResources::Npcs_BalmerPeaks_Bodom_Animations,
	EntityResources::Npcs_BalmerPeaks_Bodom_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Bodom::~Bodom()
{
}

Vec2 Bodom::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bodom::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Bodom::create();
}
