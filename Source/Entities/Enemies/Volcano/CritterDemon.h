#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class CritterDemon : public Enemy
{
public:
	static CritterDemon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyCritterDemon;

private:
	CritterDemon(ValueMap* initProperties);
	~CritterDemon();
};
