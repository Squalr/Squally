#include "Warlock.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Warlock::MapKey = "warlock";

Warlock* Warlock::deserialize(ValueMap& properties)
{
	Warlock* instance = new Warlock(properties);

	instance->autorelease();

	return instance;
}

Warlock::Warlock(ValueMap& properties) : super(properties,
	Warlock::MapKey,
	EntityResources::Enemies_VoidStar_Warlock_Animations,
	EntityResources::Enemies_VoidStar_Warlock_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Warlock::~Warlock()
{
}

Vec2 Warlock::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Warlock::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Warlock::create();
}
