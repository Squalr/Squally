#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Harpy : public Enemy
{
public:
	static Harpy * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyHarpy;

private:
	Harpy(ValueMap* initProperties);
	~Harpy();
};
