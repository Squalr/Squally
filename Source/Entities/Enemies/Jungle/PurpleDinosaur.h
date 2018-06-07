#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class PurpleDinosaur : public Enemy
{
public:
	static PurpleDinosaur * create();

private:
	PurpleDinosaur();
	~PurpleDinosaur();
};
