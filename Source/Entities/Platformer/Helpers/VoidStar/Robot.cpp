#include "Robot.h"

#include "cocos/math/CCGeometry.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Robot::MapKey = "robot";

Robot* Robot::deserialize(ValueMap& properties)
{
	Robot* instance = new Robot(properties);

	instance->autorelease();

	return instance;
}

Robot::Robot(ValueMap& properties) : super(properties,
	Robot::MapKey,
	EntityResources::Helpers_VoidStar_Robot_Animations,
	EntityResources::Helpers_VoidStar_Robot_Emblem,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f))
{
}

Robot::~Robot()
{
}

Vec2 Robot::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Robot::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_VoidStar_Robot::create();
}
