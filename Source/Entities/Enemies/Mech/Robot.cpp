#include "Robot.h"

const std::string Robot::KeyEnemyRobot = "robot";

Robot* Robot::create()
{
	Robot* instance = new Robot();

	instance->autorelease();

	return instance;
}

Robot::Robot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_Robot_Animations,
	false,
	Size(512.0f, 820.0f),
	0.3f,
	Vec2(-24.0f, -410.0f))
{
}

Robot::~Robot()
{
}
