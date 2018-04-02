#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Minotaur : public Enemy
{
public:
	static Minotaur * create();

private:
	Minotaur();
	~Minotaur();
};
