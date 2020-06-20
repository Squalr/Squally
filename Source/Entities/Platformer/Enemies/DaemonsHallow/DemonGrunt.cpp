#include "DemonGrunt.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonGrunt::MapKey = "demon-grunt";

DemonGrunt* DemonGrunt::deserialize(ValueMap& properties)
{
	DemonGrunt* instance = new DemonGrunt(properties);

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt(ValueMap& properties) : super(properties,
	DemonGrunt::MapKey,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Emblem,
	Size(312.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonGrunt::~DemonGrunt()
{
}

Vec2 DemonGrunt::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* DemonGrunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DaemonsHallow_DemonGrunt::create();
}
