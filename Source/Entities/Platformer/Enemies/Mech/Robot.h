#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Robot : public PlatformerEnemy
{
public:
	static Robot * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyRobot;

private:
	Robot(ValueMap* initProperties);
	~Robot();
};
