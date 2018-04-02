#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MantisDragon : public Enemy
{
public:
	static MantisDragon * create();

private:
	MantisDragon();
	~MantisDragon();
};
