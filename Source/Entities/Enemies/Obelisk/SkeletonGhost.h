#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonGhost : public Enemy
{
public:
	static SkeletonGhost * create();

private:
	SkeletonGhost();
	~SkeletonGhost();
};
