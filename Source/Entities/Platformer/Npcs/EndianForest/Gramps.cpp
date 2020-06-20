#include "Gramps.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gramps::MapKey = "gramps";

Gramps* Gramps::deserialize(ValueMap& properties)
{
	Gramps* instance = new Gramps(properties);

	instance->autorelease();

	return instance;
}

Gramps::Gramps(ValueMap& properties) : super(properties,
	Gramps::MapKey,
	EntityResources::Npcs_EndianForest_Gramps_Animations,
	EntityResources::Npcs_EndianForest_Gramps_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Gramps::~Gramps()
{
}

Vec2 Gramps::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Gramps::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Gramps::create();
}
