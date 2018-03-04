#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Config
{
public:

	static const float endTurnDelay;
	static const float enemyEndTurnDelay;
	static const float insertDelay;
	static const float cardDrawDelay;
	static const float revealDelay;

	static const float enemyHandWidth;
	static const float handWidth;
	static const float rowWidth;

	static const float defaultCardSpacing;
	static const float rightColumnCenter;
	static const float leftColumnCenter;
	static const float centerColumnCenter;
	static const float cardTotalOffsetX;
	static const float emblemOffsetX;
	static const float frameOffsetX;
	static const float frameOffsetY;
	static const float deckOffsetX;
	static const float deckOffsetY;
	static const float handOffsetY;
	static const float enemyHandOffscreenY;
	static const float boardCenterOffsetY;
	static const float binaryRowOffsetY;
	static const float decimalRowOffsetY;
	static const float hexRowOffsetY;
	static const float labelsOffsetY;
	static const float previewOffsetY;
	static const float graveyardOffsetX;
	static const float graveyardOffsetY;
	static const float handCardCountOffsetX;
	static const float socketOffsetY;
	static const float socketAOffsetX;
	static const float socketBOffsetX;
};

