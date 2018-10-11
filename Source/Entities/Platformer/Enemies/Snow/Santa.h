#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Santa : public PlatformerEnemy
{
public:
	static Santa * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySanta;

private:
	Santa(ValueMap* initProperties);
	~Santa();
};
