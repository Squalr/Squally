#pragma once
#include "cocos2d.h"

#include "Resources.h"

#include "Card.h"

using namespace cocos2d;

class CardStorage : public GameObject
{
public:
	static CardStorage * create();

private:
	CardStorage();
	~CardStorage();
};

