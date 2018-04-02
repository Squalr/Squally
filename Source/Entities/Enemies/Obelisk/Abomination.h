#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Abomination : public Enemy
{
public:
	static Abomination * create();

private:
	Abomination();
	~Abomination();
};
