#include "PenaltyDiscardBanner.h"

PenaltyDiscardBanner* PenaltyDiscardBanner::create()
{
	PenaltyDiscardBanner* instance = new PenaltyDiscardBanner();

	instance->autorelease();

	return instance;
}

PenaltyDiscardBanner::PenaltyDiscardBanner()
{
}

PenaltyDiscardBanner::~PenaltyDiscardBanner()
{
}

void PenaltyDiscardBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void PenaltyDiscardBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PenaltyDiscardBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	if (gameState->stateType == GameState::PenaltyDiscard)
	{
		if (gameState->penaltyCardsPlayed > 0)
		{
			this->setBannerText("REMAINING DISCARDS: " + std::to_string(gameState->penaltyCardsPlayed));
			this->showBanner();
		}
	}
	else if (gameState->previousStateType == GameState::PenaltyDiscard)
	{
		this->hideBanner();
	}
}
