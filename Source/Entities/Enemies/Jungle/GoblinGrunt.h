#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinGrunt : public Enemy
{
public:
	static GoblinGrunt * create();

private:
	GoblinGrunt();
	~GoblinGrunt();
};
