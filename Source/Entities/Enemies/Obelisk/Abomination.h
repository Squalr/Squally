#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Abomination : public Enemy
{
public:
	static Abomination * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAbomination;

private:
	Abomination(ValueMap* initProperties);
	~Abomination();
};
