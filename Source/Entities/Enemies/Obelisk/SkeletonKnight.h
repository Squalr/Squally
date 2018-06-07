#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonKnight : public Enemy
{
public:
	static SkeletonKnight * create();

private:
	SkeletonKnight();
	~SkeletonKnight();
};
