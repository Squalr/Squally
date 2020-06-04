#include "Krampus.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Krampus::MapKey = "krampus";

Krampus* Krampus::deserialize(ValueMap& properties)
{
	Krampus* instance = new Krampus(properties);

	instance->autorelease();

	return instance;
}

Krampus::Krampus(ValueMap& properties) : super(properties,
	Krampus::MapKey,
	EntityResources::Enemies_DataMines_Krampus_Animations,
	EntityResources::Enemies_DataMines_Krampus_Emblem,
	Size(396.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Krampus::~Krampus()
{
}

Vec2 Krampus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Krampus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_Krampus::create();
}
