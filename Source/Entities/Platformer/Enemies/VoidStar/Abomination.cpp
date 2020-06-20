#include "Abomination.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Abomination::MapKey = "abomination";

Abomination* Abomination::deserialize(ValueMap& properties)
{
	Abomination* instance = new Abomination(properties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap& properties) : super(properties,
	Abomination::MapKey,
	EntityResources::Enemies_VoidStar_Abomination_Animations,
	EntityResources::Enemies_VoidStar_Abomination_Emblem,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Abomination::~Abomination()
{
}

Vec2 Abomination::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Abomination::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_VoidStar_Abomination::create();
}
