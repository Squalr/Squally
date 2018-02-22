#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class CardStorage : public Node
{
public:
	static CardStorage * create();

private:
	CardStorage();
	~CardStorage();

	void initializePositions();
	void initializeListeners();
};

