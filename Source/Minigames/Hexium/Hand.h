#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Hand : public Node
{
public:
	static Hand * create();

private:
	Hand();
	~Hand();

	void initializePositions();
	void initializeListeners();
};

