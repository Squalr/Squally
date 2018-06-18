#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class EarthElemental : public Enemy
{
public:
	static EarthElemental * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEarthElemental;

private:
	EarthElemental(ValueMap* initProperties);
	~EarthElemental();
};
