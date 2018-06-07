#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonArcher : public Enemy
{
public:
	static DemonArcher * create();

private:
	DemonArcher();
	~DemonArcher();
};
