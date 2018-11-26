#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Santa : public PlatformerEnemy
{
public:
	static Santa* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySanta;

private:
	Santa(ValueMap* initProperties);
	~Santa();
};
