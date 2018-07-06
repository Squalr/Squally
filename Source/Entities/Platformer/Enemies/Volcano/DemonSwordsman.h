#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonSwordsman : public PlatformerEnemy
{
public:
	static DemonSwordsman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonSwordsman;

private:
	DemonSwordsman(ValueMap* initProperties);
	~DemonSwordsman();
};
