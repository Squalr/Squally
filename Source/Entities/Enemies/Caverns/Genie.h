#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Genie : public Enemy
{
public:
	static Genie * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGenie;

private:
	Genie(ValueMap* initProperties);
	~Genie();
};
