#include "Thug.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Thug::MapKey = "thug";

Thug* Thug::deserialize(ValueMap& properties)
{
	Thug* instance = new Thug(properties);

	instance->autorelease();

	return instance;
}

Thug::Thug(ValueMap& properties) : super(properties,
	Thug::MapKey,
	EntityResources::Enemies_DataMines_Thug_Animations,
	EntityResources::Enemies_DataMines_Thug_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Thug::~Thug()
{
}

Vec2 Thug::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Thug::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_Thug::create();
}
