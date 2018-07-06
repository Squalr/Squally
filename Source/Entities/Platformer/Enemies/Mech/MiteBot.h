#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MiteBot : public PlatformerEnemy
{
public:
	static MiteBot * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMiteBot;

private:
	MiteBot(ValueMap* initProperties);
	~MiteBot();
};
