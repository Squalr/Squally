#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Card : public Node
{
public:
	static Card * create();

private:
	Card();
	~Card();

	void initializePositions();
	void initializeListeners();
};

