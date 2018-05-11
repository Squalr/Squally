#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonSwordsman : public Enemy
{
public:
	static DemonSwordsman * create();

private:
	DemonSwordsman();
	~DemonSwordsman();
};
