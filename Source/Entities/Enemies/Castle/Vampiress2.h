#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Vampiress2 : public Enemy
{
public:
	static Vampiress2 * create();

private:
	Vampiress2();
	~Vampiress2();
};
