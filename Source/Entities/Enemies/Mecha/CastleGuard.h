#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class CastleGuard : public Enemy
{
public:
	static CastleGuard * create();

private:
	CastleGuard();
	~CastleGuard();
};
