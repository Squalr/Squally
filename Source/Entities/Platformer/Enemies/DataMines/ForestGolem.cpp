#include "ForestGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ForestGolem::MapKey = "forest-golem";

ForestGolem* ForestGolem::deserialize(ValueMap& properties)
{
	ForestGolem* instance = new ForestGolem(properties);

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem(ValueMap& properties) : super(properties,
	ForestGolem::MapKey,
	EntityResources::Enemies_DataMines_ForestGolem_Animations,
	EntityResources::Enemies_DataMines_ForestGolem_Emblem,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

ForestGolem::~ForestGolem()
{
}

Vec2 ForestGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* ForestGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_DataMines_ForestGolem::create();
}
