#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class KingGrogg : public PlatformerEnemy
{
public:
	static KingGrogg * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyKingGrogg;

private:
	KingGrogg(ValueMap* initProperties);
	~KingGrogg();
};
