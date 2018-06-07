#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class PigDemon : public Enemy
{
public:
	static PigDemon * create();

private:
	PigDemon();
	~PigDemon();
};
