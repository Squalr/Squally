#include "Thurstan.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Thurstan::MapKey = "thurstan";

Thurstan* Thurstan::deserialize(ValueMap& properties)
{
	Thurstan* instance = new Thurstan(properties);

	instance->autorelease();

	return instance;
}

Thurstan::Thurstan(ValueMap& properties) : super(properties,
	Thurstan::MapKey,
	EntityResources::Npcs_CastleValgrind_Thurstan_Animations,
	EntityResources::Npcs_CastleValgrind_Thurstan_Emblem,
	Size(124.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Thurstan::~Thurstan()
{
}

Vec2 Thurstan::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Thurstan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Thurstan::create();
}
