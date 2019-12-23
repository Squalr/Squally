#include "GoblinShaman.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoblinShaman::MapKeyGoblinShaman = "goblin-shaman";

GoblinShaman* GoblinShaman::deserialize(ValueMap& properties)
{
	GoblinShaman* instance = new GoblinShaman(properties);

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman(ValueMap& properties) : super(properties,
	GoblinShaman::MapKeyGoblinShaman,
	EntityResources::Enemies_EndianForest_GoblinShaman_Animations,
	EntityResources::Enemies_EndianForest_GoblinShaman_Emblem,
	Size(96.0f, 204.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

GoblinShaman::~GoblinShaman()
{
}

Vec2 GoblinShaman::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* GoblinShaman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_GoblinShaman::create();
}
