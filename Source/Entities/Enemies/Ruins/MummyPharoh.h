#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MummyPharoh : public Enemy
{
public:
	static MummyPharoh * create();

private:
	MummyPharoh();
	~MummyPharoh();
};
