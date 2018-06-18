#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Ent : public Enemy
{
public:
	static Ent * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEnt;

private:
	Ent(ValueMap* initProperties);
	~Ent();
};
