#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"

using namespace cocos2d;

class Deck : public Node
{
public:
	static Deck * create();

	Card* drawCard();

private:
	Deck();
	~Deck();

	void initializePositions();
	void initializeListeners();
};

