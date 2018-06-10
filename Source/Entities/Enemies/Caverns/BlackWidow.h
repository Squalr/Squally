#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BlackWidow : public Enemy
{
public:
	static BlackWidow * create();

private:
	BlackWidow();
	~BlackWidow();
};
