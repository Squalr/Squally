#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class MummyPharaoh : public Enemy
{
public:
	static MummyPharaoh * create();

	static const std::string KeyEnemyMummyPharaoh;

private:
	MummyPharaoh();
	~MummyPharaoh();
};
