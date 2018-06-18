#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Exterminator : public Enemy
{
public:
	static Exterminator * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyExterminator;

private:
	Exterminator(ValueMap* initProperties);
	~Exterminator();
};
