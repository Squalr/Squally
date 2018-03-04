#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Config
{
public:

	static const int startingCardAmount;
	static const float endTurnDelay;
	static const float enemyDrawDelay;
	static const float turnAnimationDelay;
	static const float enemyEndTurnDelay;
	static const float insertDelay;
	static const float cardDrawDelay;
	static const float revealDelay;
	static const float emblemFadeSpeed;
	static const float skullFadeSpeed;

	static const float coinFlipStartScale;
	static const float coinFlipEndScale;
	static const float coinFlipUpDuration;
	static const float coinFlipDownDuration;
	static const float coinFlipSpeed;
	static const float coinFlipRestDuration;
	static const float coinFlipFadeSpeed;
	static const int coinFlipCount;

	static const float enemyHandWidth;
	static const float handWidth;
	static const float rowWidth;

	static const float defaultCardSpacing;
	static const float rightColumnCenter;
	static const float leftColumnCenter;
	static const float centerColumnCenter;
	static const float cardTotalOffsetX;
	static const float frameOffsetX;
	static const float frameOffsetY;
	static const float deckOffsetX;
	static const float deckOffsetY;
	static const float deckCardCountOffsetY;
	static const float handOffsetY;
	static const float handCountOffsetX;
	static const float handCountOffsetY;
	static const float enemyHandOffscreenY;
	static const float boardCenterOffsetY;
	static const float binaryRowOffsetY;
	static const float decimalRowOffsetY;
	static const float hexRowOffsetY;
	static const float previewOffsetY;
	static const float graveyardOffsetX;
	static const float graveyardOffsetY;
	static const float socketOffsetY;
	static const float socketAOffsetX;
	static const float socketBOffsetX;
	static const float totalAttackOffsetX;
	static const float totalAttackOffsetY;
	static const float leaderEmblemOffsetY;
};

