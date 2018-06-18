#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class FireElemental : public Enemy
{
public:
	static FireElemental * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyFireElemental;

private:
	FireElemental(ValueMap* initProperties);
	~FireElemental();
};
