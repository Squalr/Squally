#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechBoxDrone : public Enemy
{
public:
	static MechBoxDrone * create();

private:
	MechBoxDrone();
	~MechBoxDrone();
};
