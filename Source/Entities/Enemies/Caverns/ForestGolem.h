#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class ForestGolem : public Enemy
{
public:
	static ForestGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyForestGolem;

private:
	ForestGolem(ValueMap* initProperties);
	~ForestGolem();
};
