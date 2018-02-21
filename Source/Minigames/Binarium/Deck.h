#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Deck : public Node
{
public:
	static Deck * create();

private:
	Deck();
	~Deck();

	void initializePositions();
	void initializeListeners();
};

