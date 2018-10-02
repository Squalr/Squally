#include "CardReplaceBanner.h"

CardReplaceBanner* CardReplaceBanner::create()
{
	CardReplaceBanner* instance = new CardReplaceBanner();

	instance->autorelease();

	return instance;
}

CardReplaceBanner::CardReplaceBanner()
{
}

CardReplaceBanner::~CardReplaceBanner()
{
}

void CardReplaceBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void CardReplaceBanner::onStateChange(GameState* gameState)
{
	if (gameState->stateType == GameState::CardReplace)
	{
		this->setBannerText("REMAINING CARD REPLACEMENTS: " + std::to_string(gameState->cardReplaceCount));
		this->showBanner();
	}
}
