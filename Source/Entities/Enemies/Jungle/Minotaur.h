#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Minotaur : public Enemy
{
public:
	static Minotaur * create();

private:
	Minotaur();
	~Minotaur();
};
