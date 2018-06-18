#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class EarthGolem : public Enemy
{
public:
	static EarthGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEarthGolem;

private:
	EarthGolem(ValueMap* initProperties);
	~EarthGolem();
};
