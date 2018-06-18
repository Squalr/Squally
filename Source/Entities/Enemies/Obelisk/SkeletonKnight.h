#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonKnight : public Enemy
{
public:
	static SkeletonKnight * create();

	static const std::string KeyEnemySkeletonKnight;

private:
	SkeletonKnight();
	~SkeletonKnight();
};
