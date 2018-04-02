#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BlueGoblin : public Enemy
{
public:
	static BlueGoblin * create();

private:
	BlueGoblin();
	~BlueGoblin();
};
