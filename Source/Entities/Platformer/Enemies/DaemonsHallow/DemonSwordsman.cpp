#include "DemonSwordsman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonSwordsman::MapKey = "demon-swordsman";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap& properties)
{
	DemonSwordsman* instance = new DemonSwordsman(properties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap& properties) : super(properties,
	DemonSwordsman::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Emblem,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonSwordsman::~DemonSwordsman()
{
}

Vec2 DemonSwordsman::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonSwordsman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonSwordsman::create();
}
