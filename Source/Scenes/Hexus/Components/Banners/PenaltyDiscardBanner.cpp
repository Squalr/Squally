#include "PenaltyDiscardBanner.h"

PenaltyDiscardBanner* PenaltyDiscardBanner::create()
{
	PenaltyDiscardBanner* instance = new PenaltyDiscardBanner();

	instance->autorelease();

	return instance;
}

PenaltyDiscardBanner::PenaltyDiscardBanner()
{
	this->penaltyIcon = Sprite::create(Resources::Minigames_Hexus_PenaltyCardsIconLarge);
	this->penaltyIconParticles = ParticleSystemQuad::create(Resources::Particles_PurpleAuraLarge);

	this->penaltyIconParticles->setVisible(false);

	this->addBannerChild(this->penaltyIconParticles);
	this->addBannerChild(this->penaltyIcon);
}

PenaltyDiscardBanner::~PenaltyDiscardBanner()
{
}

void PenaltyDiscardBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->penaltyIconParticles->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f));
	this->penaltyIcon->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f));
}

void PenaltyDiscardBanner::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void PenaltyDiscardBanner::onStateChange(GameState* gameState)
{
	BannerBase::onStateChange(gameState);

	// Disabled
	return;

	if (gameState->stateType == GameState::PenaltyDiscard)
	{
		if (gameState->enemyLastStanded && gameState->penaltyCardsPlayed > 0)
		{
			this->setBannerText("REMAINING DISCARDS: " + std::to_string(gameState->penaltyCardsPlayed));
			this->showBanner();

			this->penaltyIconParticles->start();
			this->penaltyIconParticles->setVisible(true);
		}
	}
	else if (gameState->previousStateType == GameState::PenaltyDiscard)
	{
		this->hideBanner();

		this->penaltyIconParticles->stop();
		this->penaltyIconParticles->setVisible(false);
	}
}
