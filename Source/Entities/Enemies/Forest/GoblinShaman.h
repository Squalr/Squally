#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GoblinShaman : public Enemy
{
public:
	static GoblinShaman * create();

private:
	GoblinShaman();
	~GoblinShaman();
};
