#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Cyclops : public Enemy
{
public:
	static Cyclops * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyCyclops;

private:
	Cyclops(ValueMap* initProperties);
	~Cyclops();
};
