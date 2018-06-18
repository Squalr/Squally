#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossSanta : public Enemy
{
public:
	static BossSanta * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossSanta;

private:
	BossSanta(ValueMap* initProperties);
	~BossSanta();
};
