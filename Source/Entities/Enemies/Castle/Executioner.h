#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Executioner : public Enemy
{
public:
	static Executioner * create();

private:
	Executioner();
	~Executioner();
};
