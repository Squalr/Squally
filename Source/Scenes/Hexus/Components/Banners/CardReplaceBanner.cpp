#include "CardReplaceBanner.h"

CardReplaceBanner* CardReplaceBanner::create()
{
	CardReplaceBanner* instance = new CardReplaceBanner();

	instance->autorelease();

	return instance;
}

CardReplaceBanner::CardReplaceBanner()
{
	this->penaltyIcon = Sprite::create(Resources::Minigames_Hexus_PenaltyCardsIconLarge);
	this->penaltyIconParticles = ParticleSystemQuad::create(Resources::Particles_PurpleAuraLarge);

	this->penaltyIconParticles->setVisible(false);

	this->addBannerChild(this->penaltyIconParticles);
	this->addBannerChild(this->penaltyIcon);
}

CardReplaceBanner::~CardReplaceBanner()
{
}

void CardReplaceBanner::initializePositions()
{
	BannerBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->penaltyIconParticles->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f));
	this->penaltyIcon->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f));
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
		if (gameState->cardReplaceCount > 0)
		{
			this->setBannerText("REMAINING CARD REPLACEMENTS: " + std::to_string(gameState->cardReplaceCount));
			this->showBanner();

			this->penaltyIconParticles->start();
			this->penaltyIconParticles->setVisible(true);
		}
	}
	else if (gameState->previousStateType == GameState::CardReplace)
	{
		this->hideBanner();

		this->penaltyIconParticles->stop();
		this->penaltyIconParticles->setVisible(false);
	}
}
