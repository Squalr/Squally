#include "Burch.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Burch::MapKey = "burch";

Burch* Burch::deserialize(ValueMap& properties)
{
	Burch* instance = new Burch(properties);

	instance->autorelease();

	return instance;
}

Burch::Burch(ValueMap& properties) : super(properties,
	Burch::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Burch_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Burch_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Burch::~Burch()
{
}

Vec2 Burch::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Burch::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Burch::create();
}
