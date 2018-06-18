#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Ghost : public Enemy
{
public:
	static Ghost * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGhost;

private:
	Ghost(ValueMap* initProperties);
	~Ghost();
};
