#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Vampiress : public Enemy
{
public:
	static Vampiress * create();

private:
	Vampiress();
	~Vampiress();
};
