#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Abomination : public Enemy
{
public:
	static Abomination * create();

private:
	Abomination();
	~Abomination();
};
