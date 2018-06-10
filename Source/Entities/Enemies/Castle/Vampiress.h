#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Vampiress : public Enemy
{
public:
	static Vampiress * create();

private:
	Vampiress();
	~Vampiress();
};
