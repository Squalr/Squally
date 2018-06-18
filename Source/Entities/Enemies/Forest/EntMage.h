#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class EntMage : public Enemy
{
public:
	static EntMage * create();

	static const std::string KeyEnemyEntMage;

private:
	EntMage();
	~EntMage();
};
