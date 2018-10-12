#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MummyPriest : public PlatformerEnemy
{
public:
	static MummyPriest * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMummyPriest;

private:
	MummyPriest(ValueMap* initProperties);
	~MummyPriest();
};
