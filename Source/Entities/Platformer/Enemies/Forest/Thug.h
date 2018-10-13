#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Thug : public PlatformerEnemy
{
public:
	static Thug * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyThug;

private:
	Thug(ValueMap* initProperties);
	~Thug();
};
