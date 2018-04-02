#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Vampiress1 : public Enemy
{
public:
	static Vampiress1 * create();

private:
	Vampiress1();
	~Vampiress1();
};
