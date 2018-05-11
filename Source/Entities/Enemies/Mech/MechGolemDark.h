#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechGolemDark : public Enemy
{
public:
	static MechGolemDark * create();

private:
	MechGolemDark();
	~MechGolemDark();
};
