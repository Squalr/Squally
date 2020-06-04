#include "Mildred.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Mildred::MapKey = "mildred";

Mildred* Mildred::deserialize(ValueMap& properties)
{
	Mildred* instance = new Mildred(properties);

	instance->autorelease();

	return instance;
}

Mildred::Mildred(ValueMap& properties) : super(properties,
	Mildred::MapKey,
	EntityResources::Npcs_DataMines_Mildred_Animations,
	EntityResources::Npcs_DataMines_Mildred_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Mildred::~Mildred()
{
}

Vec2 Mildred::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Mildred::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Mildred::create();
}
