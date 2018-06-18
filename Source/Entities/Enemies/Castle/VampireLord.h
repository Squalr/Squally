#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VampireLord : public Enemy
{
public:
	static VampireLord * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyVampireLord;

private:
	VampireLord(ValueMap* initProperties);
	~VampireLord();
};
