#include "OrcGrunt.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OrcGrunt::MapKeyOrcGrunt = "orc-grunt";

OrcGrunt* OrcGrunt::deserialize(ValueMap& properties)
{
	OrcGrunt* instance = new OrcGrunt(properties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(ValueMap& properties) : super(properties,
	OrcGrunt::MapKeyOrcGrunt,
	EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
	EntityResources::Enemies_EndianForest_OrcGrunt_Emblem,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcGrunt::~OrcGrunt()
{
}

Vec2 OrcGrunt::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* OrcGrunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcGrunt::create();
}
