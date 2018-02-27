#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"

using namespace cocos2d;

class Hand : public Node
{
public:
	static Hand * create();

	void insertCard(Card* card);
	void clear();

private:
	Hand();
	~Hand();

	void initializePositions();
	void initializeListeners();
};

