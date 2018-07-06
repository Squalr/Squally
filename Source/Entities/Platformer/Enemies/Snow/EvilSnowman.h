#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class EvilSnowman : public PlatformerEnemy
{
public:
	static EvilSnowman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEvilSnowman;

private:
	EvilSnowman(ValueMap* initProperties);
	~EvilSnowman();
};
