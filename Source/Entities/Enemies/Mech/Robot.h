#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Robot : public Enemy
{
public:
	static Robot * create();

	static const std::string KeyEnemyRobot;

private:
	Robot();
	~Robot();
};
