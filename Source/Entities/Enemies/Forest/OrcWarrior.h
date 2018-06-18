#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class OrcWarrior : public Enemy
{
public:
	static OrcWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyOrcWarrior;

private:
	OrcWarrior(ValueMap* initProperties);
	~OrcWarrior();
};
