#include "Bonnie.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bonnie::MapKey = "bonnie";

Bonnie* Bonnie::deserialize(ValueMap& properties)
{
	Bonnie* instance = new Bonnie(properties);

	instance->autorelease();

	return instance;
}

Bonnie::Bonnie(ValueMap& properties) : super(properties,
	Bonnie::MapKey,
	EntityResources::Npcs_DataMines_Bonnie_Animations,
	EntityResources::Npcs_DataMines_Bonnie_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Bonnie::~Bonnie()
{
}

Vec2 Bonnie::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bonnie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Bonnie::create();
}
