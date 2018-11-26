#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class EvilEye : public PlatformerEnemy
{
public:
	static EvilEye* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyEvilEye;

private:
	EvilEye(ValueMap* initProperties);
	~EvilEye();
};
