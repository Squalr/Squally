#include "DemonDragon.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonDragon::MapKey = "demon-dragon";

DemonDragon* DemonDragon::deserialize(ValueMap& properties)
{
	DemonDragon* instance = new DemonDragon(properties);

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon(ValueMap& properties) : super(properties,
	DemonDragon::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Emblem,
	Size(340.0f, 360.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

DemonDragon::~DemonDragon()
{
}

Vec2 DemonDragon::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonDragon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonDragon::create();
}
