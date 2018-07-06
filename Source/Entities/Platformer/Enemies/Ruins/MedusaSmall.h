#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MedusaSmall : public PlatformerEnemy
{
public:
	static MedusaSmall * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMedusaSmall;

private:
	MedusaSmall(ValueMap* initProperties);
	~MedusaSmall();
};
