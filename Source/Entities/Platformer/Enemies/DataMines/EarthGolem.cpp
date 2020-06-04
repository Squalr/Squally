#include "EarthGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EarthGolem::MapKey = "earth-golem";

EarthGolem* EarthGolem::deserialize(ValueMap& properties)
{
	EarthGolem* instance = new EarthGolem(properties);

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem(ValueMap& properties) : super(properties,
	EarthGolem::MapKey,
	EntityResources::Enemies_DataMines_EarthGolem_Animations,
	EntityResources::Enemies_DataMines_EarthGolem_Emblem,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

EarthGolem::~EarthGolem()
{
}

Vec2 EarthGolem::getDialogueOffset()
{
	return Vec2(-48.0f, -144.0f);
}

LocalizedString* EarthGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_EarthGolem::create();
}
