#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BoarGoblin : public Enemy
{
public:
	static BoarGoblin * create();

private:
	BoarGoblin();
	~BoarGoblin();
};
