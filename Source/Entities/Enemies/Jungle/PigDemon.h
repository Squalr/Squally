#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class PigDemon : public Enemy
{
public:
	static PigDemon * create();

private:
	PigDemon();
	~PigDemon();
};
