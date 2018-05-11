#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class EntMage : public Enemy
{
public:
	static EntMage * create();

private:
	EntMage();
	~EntMage();
};
