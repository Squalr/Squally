#include "Fraya.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Fraya::MapKey = "fraya";

Fraya* Fraya::deserialize(ValueMap& properties)
{
	Fraya* instance = new Fraya(properties);

	instance->autorelease();

	return instance;
}

Fraya::Fraya(ValueMap& properties) : super(properties,
	Fraya::MapKey,
	EntityResources::Npcs_DataMines_Fraya_Animations,
	EntityResources::Npcs_DataMines_Fraya_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Fraya::~Fraya()
{
}

Vec2 Fraya::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Fraya::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DataMines_Fraya::create();
}
