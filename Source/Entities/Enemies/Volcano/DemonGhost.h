#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonGhost : public Enemy
{
public:
	static DemonGhost * create();

private:
	DemonGhost();
	~DemonGhost();
};
