#include "OrcBomber.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OrcBomber::MapKey = "orc-bomber";

OrcBomber* OrcBomber::deserialize(ValueMap& properties)
{
	OrcBomber* instance = new OrcBomber(properties);

	instance->autorelease();

	return instance;
}

OrcBomber::OrcBomber(ValueMap& properties) : super(properties,
	OrcBomber::MapKey,
	EntityResources::Enemies_EndianForest_OrcBomber_Animations,
	EntityResources::Enemies_EndianForest_OrcBomber_Emblem,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcBomber::~OrcBomber()
{
}

Vec2 OrcBomber::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* OrcBomber::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcBomber::create();
}
