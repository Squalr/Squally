#include "ToySoldierGoblin.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ToySoldierGoblin::MapKey = "toy-soldier-goblin";

ToySoldierGoblin* ToySoldierGoblin::deserialize(ValueMap& properties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(properties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(ValueMap& properties) : super(properties,
	ToySoldierGoblin::MapKey,
	EntityResources::Enemies_BallmerPeaks_ToySoldierGoblin_Animations,
	EntityResources::Enemies_BallmerPeaks_ToySoldierGoblin_Emblem,
	Size(112.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}

Vec2 ToySoldierGoblin::getDialogueOffset()
{
	return Vec2(-32.0f, -144.0f);
}

LocalizedString* ToySoldierGoblin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BallmerPeaks_ToySoldierGoblin::create();
}
