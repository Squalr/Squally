#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class LavaGolem : public Enemy
{
public:
	static LavaGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyLavaGolem;

private:
	LavaGolem(ValueMap* initProperties);
	~LavaGolem();
};
