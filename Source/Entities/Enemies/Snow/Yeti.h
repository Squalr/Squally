#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Yeti : public Enemy
{
public:
	static Yeti * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyYeti;

private:
	Yeti(ValueMap* initProperties);
	~Yeti();
};
