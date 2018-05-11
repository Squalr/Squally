#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class MiteBot : public Enemy
{
public:
	static MiteBot * create();

private:
	MiteBot();
	~MiteBot();
};
