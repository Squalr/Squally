#include "Turtle.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Turtle::MapKey = "turtle";

Turtle* Turtle::deserialize(ValueMap& properties)
{
	Turtle* instance = new Turtle(properties);

	instance->autorelease();

	return instance;
}

Turtle::Turtle(ValueMap& properties) : super(properties,
	Turtle::MapKey,
	EntityResources::Helpers_EndianForest_Turtle_Animations,
	EntityResources::Helpers_EndianForest_Turtle_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Turtle::~Turtle()
{
}

Vec2 Turtle::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Turtle::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Turtle::create();
}
