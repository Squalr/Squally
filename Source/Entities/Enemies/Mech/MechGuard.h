#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MechGuard : public Enemy
{
public:
	static MechGuard * create();

private:
	MechGuard();
	~MechGuard();
};
