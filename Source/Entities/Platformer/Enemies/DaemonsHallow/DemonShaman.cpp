#include "DemonShaman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonShaman::MapKey = "demon-shaman";

DemonShaman* DemonShaman::deserialize(ValueMap& properties)
{
	DemonShaman* instance = new DemonShaman(properties);

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman(ValueMap& properties) : super(properties,
	DemonShaman::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonShaman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonShaman_Emblem,
	Size(212.0f, 280.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonShaman::~DemonShaman()
{
}

Vec2 DemonShaman::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonShaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonShaman::create();
}
