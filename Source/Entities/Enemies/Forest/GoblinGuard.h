#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGuard : public Enemy
{
public:
	static GoblinGuard * create();

private:
	GoblinGuard();
	~GoblinGuard();
};
