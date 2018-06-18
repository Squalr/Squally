#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class TikiGolem : public Enemy
{
public:
	static TikiGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTikiGolem;

private:
	TikiGolem(ValueMap* initProperties);
	~TikiGolem();
};
