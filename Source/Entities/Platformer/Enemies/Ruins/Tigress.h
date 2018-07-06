#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Tigress : public PlatformerEnemy
{
public:
	static Tigress * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTigress;

private:
	Tigress(ValueMap* initProperties);
	~Tigress();
};
