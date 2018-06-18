#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BatDemon : public Enemy
{
public:
	static BatDemon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBatDemon;

private:
	BatDemon(ValueMap* initProperties);
	~BatDemon();
};
