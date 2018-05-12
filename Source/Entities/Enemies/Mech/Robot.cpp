#include "Robot.h"

Robot* Robot::create()
{
	Robot* instance = new Robot();

	instance->autorelease();

	return instance;
}

Robot::Robot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_Robot_Animations,
	false)
{
}

Robot::~Robot()
{
}
