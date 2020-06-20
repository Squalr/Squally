#include "Shaman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Shaman::MapKey = "shaman";

Shaman* Shaman::deserialize(ValueMap& properties)
{
	Shaman* instance = new Shaman(properties);

	instance->autorelease();

	return instance;
}

Shaman::Shaman(ValueMap& properties) : super(properties,
	Shaman::MapKey,
	EntityResources::Enemies_DataMines_Shaman_Animations,
	EntityResources::Enemies_DataMines_Shaman_Emblem,
	Size(256.0f, 288.0f),
	0.78f,
	Vec2(0.0f, 0.0f))
{
}

Shaman::~Shaman()
{
}

Vec2 Shaman::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Shaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_Shaman::create();
}
