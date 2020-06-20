#include "Lucifer.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Lucifer::MapKey = "lucifer";

Lucifer* Lucifer::deserialize(ValueMap& properties)
{
	Lucifer* instance = new Lucifer(properties);

	instance->autorelease();

	return instance;
}

Lucifer::Lucifer(ValueMap& properties) : super(properties,
	Lucifer::MapKey,
	EntityResources::Npcs_DaemonsHallow_Lucifer_Animations,
	EntityResources::Npcs_DaemonsHallow_Lucifer_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
}

Lucifer::~Lucifer()
{
}

Vec2 Lucifer::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Lucifer::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Lucifer::create();
}
