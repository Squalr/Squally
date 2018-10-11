#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Shade : public PlatformerEnemy
{
public:
	static Shade * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyShade;

private:
	Shade(ValueMap* initProperties);
	~Shade();
};
