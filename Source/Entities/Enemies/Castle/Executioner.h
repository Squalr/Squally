#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Executioner : public Enemy
{
public:
	static Executioner * create();

private:
	Executioner();
	~Executioner();
};
