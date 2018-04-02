#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class VoidDemon : public Enemy
{
public:
	static VoidDemon * create();

private:
	VoidDemon();
	~VoidDemon();
};
