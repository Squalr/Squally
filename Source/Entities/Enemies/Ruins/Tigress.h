#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Tigress : public Enemy
{
public:
	static Tigress * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTigress;

private:
	Tigress(ValueMap* initProperties);
	~Tigress();
};
