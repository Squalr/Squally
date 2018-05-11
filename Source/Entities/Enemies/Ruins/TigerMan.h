#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class TigerMan : public Enemy
{
public:
	static TigerMan * create();

private:
	TigerMan();
	~TigerMan();
};
