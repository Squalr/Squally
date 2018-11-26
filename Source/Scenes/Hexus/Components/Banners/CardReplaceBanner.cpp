#include "CardReplaceBanner.h"

CardReplaceBanner* CardReplaceBanner::create()
{
	CardReplaceBanner* instance = new CardReplaceBanner();

	instance->autorelease();

	return instance;
}

CardReplaceBanner::CardReplaceBanner()
{
	this->penaltyIcon = Sprite::create(HexusResources::CardReplaceIconLarge);
	this->penaltyIconParticles = ParticleSystemQuad::create(ParticleResources::Hexus_PurpleAuraLarge);

	this->addBannerChild(this->penaltyIconParticles);
	this->addBannerChild(this->penaltyIcon);
}

CardReplaceBanner::~CardReplaceBanner()
{
}

void CardReplaceBanner::onEnter()
{
	BannerBase::onEnter();

	this->penaltyIconParticles->setVisible(false);
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

void CardReplaceBanner::onAnyStateChange(GameState* gameState)
{
	BannerBase::onAnyStateChange(gameState);

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
