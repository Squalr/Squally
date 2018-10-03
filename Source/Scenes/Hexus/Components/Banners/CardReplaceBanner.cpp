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

void CardReplaceBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void CardReplaceBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::CardReplace)
	{
		this->setBannerText("REMAINING CARD REPLACEMENTS: " + std::to_string(gameState->cardReplaceCount));
		this->showBanner();
	}
	else if (gameState->previousStateType == GameState::CardReplace)
	{
		this->hideBanner();
	}
}
