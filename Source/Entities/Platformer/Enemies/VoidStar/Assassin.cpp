#include "Assassin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Assassin::MapKey = "assassin";

Assassin* Assassin::deserialize(ValueMap& properties)
{
	Assassin* instance = new Assassin(properties);

	instance->autorelease();

	return instance;
}

Assassin::Assassin(ValueMap& properties) : super(properties,
	Assassin::MapKey,
	EntityResources::Enemies_VoidStar_Assassin_Animations,
	EntityResources::Enemies_VoidStar_Assassin_Emblem,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Assassin::~Assassin()
{
}

Vec2 Assassin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Assassin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Assassin::create();
}
