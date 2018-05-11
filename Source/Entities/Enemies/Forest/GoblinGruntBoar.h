#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GoblinGruntBoar : public Enemy
{
public:
	static GoblinGruntBoar * create();

private:
	GoblinGruntBoar();
	~GoblinGruntBoar();
};
