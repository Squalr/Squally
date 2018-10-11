#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class LightningGolem : public PlatformerEnemy
{
public:
	static LightningGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyLightningGolem;

private:
	LightningGolem(ValueMap* initProperties);
	~LightningGolem();
};
