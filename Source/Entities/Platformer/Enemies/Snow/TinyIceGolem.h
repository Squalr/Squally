#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class TinyIceGolem : public PlatformerEnemy
{
public:
	static TinyIceGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTinyIceGolem;

private:
	TinyIceGolem(ValueMap* initProperties);
	~TinyIceGolem();
};
