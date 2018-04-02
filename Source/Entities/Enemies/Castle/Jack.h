#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Jack : public Enemy
{
public:
	static Jack * create();

private:
	Jack();
	~Jack();
};
