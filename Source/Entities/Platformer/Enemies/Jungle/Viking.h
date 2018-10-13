#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Viking : public PlatformerEnemy
{
public:
	static Viking * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyViking;

private:
	Viking(ValueMap* initProperties);
	~Viking();
};
