#include "Juniper.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Juniper::MapKey = "juniper";

Juniper* Juniper::deserialize(ValueMap& properties)
{
	Juniper* instance = new Juniper(properties);

	instance->autorelease();

	return instance;
}

Juniper::Juniper(ValueMap& properties) : super(properties,
	Juniper::MapKey,
	EntityResources::Npcs_BalmerPeaks_Juniper_Animations,
	EntityResources::Npcs_BalmerPeaks_Juniper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

Juniper::~Juniper()
{
}

Vec2 Juniper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Juniper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Juniper::create();
}
