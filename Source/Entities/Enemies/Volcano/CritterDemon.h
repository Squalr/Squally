#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class CritterDemon : public Enemy
{
public:
	static CritterDemon * create();

private:
	CritterDemon();
	~CritterDemon();
};
