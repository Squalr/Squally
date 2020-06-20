#include "Undead.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Undead::MapKey = "undead";

Undead* Undead::deserialize(ValueMap& properties)
{
	Undead* instance = new Undead(properties);

	instance->autorelease();

	return instance;
}

Undead::Undead(ValueMap& properties) : super(properties,
	Undead::MapKey,
	EntityResources::Enemies_LambdaCrypts_Undead_Animations,
	EntityResources::Enemies_LambdaCrypts_Undead_Emblem,
	Size(146.0f, 248.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Undead::~Undead()
{
}

Vec2 Undead::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Undead::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_Undead::create();
}
