#include "Robin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Robin::MapKey = "robin";

Robin* Robin::deserialize(ValueMap& properties)
{
	Robin* instance = new Robin(properties);

	instance->autorelease();

	return instance;
}

Robin::Robin(ValueMap& properties) : super(properties,
	Robin::MapKey,
	EntityResources::Npcs_EndianForest_Robin_Animations,
	EntityResources::Npcs_EndianForest_Robin_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Robin::~Robin()
{
}

Vec2 Robin::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Robin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Robin::create();
}
