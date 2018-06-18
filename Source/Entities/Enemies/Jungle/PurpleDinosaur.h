#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class PurpleDinosaur : public Enemy
{
public:
	static PurpleDinosaur * create();

	static const std::string KeyEnemyPurpleDinosaur;

private:
	PurpleDinosaur();
	~PurpleDinosaur();
};
