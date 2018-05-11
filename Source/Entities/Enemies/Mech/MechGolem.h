#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechGolem : public Enemy
{
public:
	static MechGolem * create();

private:
	MechGolem();
	~MechGolem();
};
