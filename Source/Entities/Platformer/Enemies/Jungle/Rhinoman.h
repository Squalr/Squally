#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Rhinoman : public PlatformerEnemy
{
public:
	static Rhinoman* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyRhinoman;

private:
	Rhinoman(ValueMap* initProperties);
	~Rhinoman();
};
