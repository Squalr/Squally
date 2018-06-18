#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonArcher : public Enemy
{
public:
	static SkeletonArcher * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonArcher;

private:
	SkeletonArcher(ValueMap* initProperties);
	~SkeletonArcher();
};
