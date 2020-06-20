#include "Garin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Garin::MapKey = "garin";

Garin* Garin::deserialize(ValueMap& properties)
{
	Garin* instance = new Garin(properties);

	instance->autorelease();

	return instance;
}

Garin::Garin(ValueMap& properties) : super(properties,
	Garin::MapKey,
	EntityResources::Npcs_CastleValgrind_Garin_Animations,
	EntityResources::Npcs_CastleValgrind_Garin_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Garin::~Garin()
{
}

Vec2 Garin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Garin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Garin::create();
}
