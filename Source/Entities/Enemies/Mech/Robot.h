#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Robot : public Enemy
{
public:
	static Robot * create();

private:
	Robot();
	~Robot();
};
