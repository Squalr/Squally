#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Card.h"

using namespace cocos2d;

class CardStorage : public SmartNode
{
public:
	static CardStorage * create();

private:
	CardStorage();
	~CardStorage();
};

