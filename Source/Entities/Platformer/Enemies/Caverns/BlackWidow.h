#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BlackWidow : public PlatformerEnemy
{
public:
	static BlackWidow * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBlackWidow;

private:
	BlackWidow(ValueMap* initProperties);
	~BlackWidow();
};
