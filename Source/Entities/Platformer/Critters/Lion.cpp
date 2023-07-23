#include "Lion.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Lion::MapKey = "lion";

Lion* Lion::deserialize(ValueMap& properties)
{
	Lion* instance = new Lion(properties);

	instance->autorelease();

	return instance;
}

Lion::Lion(ValueMap& properties) : super(properties,
	Lion::MapKey,
	EntityResources::Misc_UnderflowRuins_Lion_Animations,
	EntityResources::Misc_UnderflowRuins_Lion_Emblem,
	CSize(192.0f, 160.0f),
	1.0f)
{
}

Lion::~Lion()
{
}

Vec2 Lion::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Lion::getEntityName()
{
	return Strings::Platformer_Entities_Names_Critters_Lion::create();
}
