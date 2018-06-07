#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Exterminator : public Enemy
{
public:
	static Exterminator * create();

private:
	Exterminator();
	~Exterminator();
};
