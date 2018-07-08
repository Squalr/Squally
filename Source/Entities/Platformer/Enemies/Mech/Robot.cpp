#include "Robot.h"

const std::string Robot::KeyEnemyRobot = "robot";

Robot* Robot::deserialize(ValueMap* initProperties)
{
	Robot* instance = new Robot(initProperties);

	instance->autorelease();

	return instance;
}

Robot::Robot(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Robot_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(512.0f, 820.0f),
	0.3f,
	Vec2(-24.0f, -410.0f))
{
}

Robot::~Robot()
{
}
