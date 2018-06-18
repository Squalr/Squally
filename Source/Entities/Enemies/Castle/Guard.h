#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Guard : public Enemy
{
public:
	static Guard * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGuard;

private:
	Guard(ValueMap* initProperties);
	~Guard();
};
