#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class CritterDemon : public Enemy
{
public:
	static CritterDemon * create();

	static const std::string KeyEnemyCritterDemon;

private:
	CritterDemon();
	~CritterDemon();
};
