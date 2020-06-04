#include "Finch.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Finch::MapKey = "finch";

Finch* Finch::deserialize(ValueMap& properties)
{
	Finch* instance = new Finch(properties);

	instance->autorelease();

	return instance;
}

Finch::Finch(ValueMap& properties) : super(properties,
	Finch::MapKey,
	EntityResources::Npcs_DataMines_Finch_Animations,
	EntityResources::Npcs_DataMines_Finch_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Finch::~Finch()
{
}

Vec2 Finch::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Finch::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Finch::create();
}
