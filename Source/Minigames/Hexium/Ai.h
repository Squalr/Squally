#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardRow.h"

using namespace cocos2d;

class Ai
{
public:
	enum Difficulty {
		Stupid,
		Easy,
		Medium,
		Hard,
		Expert,
	};

	static void performAction(Difficulty difficulty, CardRow* hand);

private:
};

