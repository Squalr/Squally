#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Scarecrow : public PlatformerEnemy
{
public:
	static Scarecrow * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyScarecrow;

private:
	Scarecrow(ValueMap* initProperties);
	~Scarecrow();
};
