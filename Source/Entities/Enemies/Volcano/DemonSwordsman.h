#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonSwordsman : public Enemy
{
public:
	static DemonSwordsman * create();

private:
	DemonSwordsman();
	~DemonSwordsman();
};
