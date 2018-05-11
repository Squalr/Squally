#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GoblinGrunt : public Enemy
{
public:
	static GoblinGrunt * create();

private:
	GoblinGrunt();
	~GoblinGrunt();
};
