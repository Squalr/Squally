#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Jack : public PlatformerEnemy
{
public:
	static Jack * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyJack;

private:
	Jack(ValueMap* initProperties);
	~Jack();
};
