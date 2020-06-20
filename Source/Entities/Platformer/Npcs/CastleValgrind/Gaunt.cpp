#include "Gaunt.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gaunt::MapKey = "gaunt";

Gaunt* Gaunt::deserialize(ValueMap& properties)
{
	Gaunt* instance = new Gaunt(properties);

	instance->autorelease();

	return instance;
}

Gaunt::Gaunt(ValueMap& properties) : super(properties,
	Gaunt::MapKey,
	EntityResources::Npcs_CastleValgrind_Gaunt_Animations,
	EntityResources::Npcs_CastleValgrind_Gaunt_Emblem,
	Size(112.0f, 160.0f),
	0.95f,
	Vec2(0.0f, 0.0f))
{
}

Gaunt::~Gaunt()
{
}

Vec2 Gaunt::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gaunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Gaunt::create();
}
