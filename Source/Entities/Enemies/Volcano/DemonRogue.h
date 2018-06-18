#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonRogue : public Enemy
{
public:
	static DemonRogue * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonRogue;

private:
	DemonRogue(ValueMap* initProperties);
	~DemonRogue();
};
