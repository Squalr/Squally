#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Vampiress : public Enemy
{
public:
	static Vampiress * create();

	static const std::string KeyEnemyVampiress;

private:
	Vampiress();
	~Vampiress();
};
