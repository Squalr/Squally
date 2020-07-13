#include "Zana.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Zana::MapKey = "zana";

Zana* Zana::deserialize(ValueMap& properties)
{
	Zana* instance = new Zana(properties);

	instance->autorelease();

	return instance;
}

Zana::Zana(ValueMap& properties) : super(properties,
	Zana::MapKey,
	EntityResources::Npcs_CastleValgrind_Zana_Animations,
	EntityResources::Npcs_CastleValgrind_Zana_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Zana::~Zana()
{
}

Vec2 Zana::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Zana::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Zana::create();
}
