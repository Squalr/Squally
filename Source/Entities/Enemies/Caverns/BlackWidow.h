#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BlackWidow : public Enemy
{
public:
	static BlackWidow * create();

private:
	BlackWidow();
	~BlackWidow();
};
