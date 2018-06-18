#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MechGolemDark : public Enemy
{
public:
	static MechGolemDark * create();

	static const std::string KeyEnemyMechGolemDark;

private:
	MechGolemDark();
	~MechGolemDark();
};
