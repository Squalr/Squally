#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Genie : public Enemy
{
public:
	static Genie * create();

private:
	Genie();
	~Genie();
};
