#include "Toben.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Toben::MapKey = "toben";

Toben* Toben::deserialize(ValueMap& properties)
{
	Toben* instance = new Toben(properties);

	instance->autorelease();

	return instance;
}

Toben::Toben(ValueMap& properties) : super(properties,
	Toben::MapKey,
	EntityResources::Npcs_EndianForest_Toben_Animations,
	EntityResources::Npcs_EndianForest_Toben_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Toben::~Toben()
{
}

Vec2 Toben::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Toben::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Toben::create();
}
