#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Shade : public PlatformerEnemy
{
public:
	static Shade* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyShade;

private:
	Shade(ValueMap* initProperties);
	~Shade();
};
