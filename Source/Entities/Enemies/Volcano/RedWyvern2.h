#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class RedWyvern2 : public Enemy
{
public:
	static RedWyvern2 * create();

private:
	RedWyvern2();
	~RedWyvern2();
};
