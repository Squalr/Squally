#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GoblinGuard : public Enemy
{
public:
	static GoblinGuard * create();

private:
	GoblinGuard();
	~GoblinGuard();
};
