#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class CritterDemon : public Enemy
{
public:
	static CritterDemon * create();

private:
	CritterDemon();
	~CritterDemon();
};
