#include "CardReplaceBanner.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Particles/SmartParticles.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"
#include "Resources/ParticleResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

CardReplaceBanner* CardReplaceBanner::create()
{
	CardReplaceBanner* instance = new CardReplaceBanner();

	instance->autorelease();

	return instance;
}

CardReplaceBanner::CardReplaceBanner()
{
	this->penaltyIcon = Sprite::create(HexusResources::CardReplaceIconLarge);
	this->penaltyIconParticles = SmartParticles::create(ParticleResources::Hexus_PurpleAuraLarge);

	this->addBannerChild(this->penaltyIconParticles);
	this->addBannerChild(this->penaltyIcon);
}

CardReplaceBanner::~CardReplaceBanner()
{
}

void CardReplaceBanner::onEnter()
{
	super::onEnter();

	this->penaltyIconParticles->setVisible(false);
}

void CardReplaceBanner::initializePositions()
{
	super::initializePositions();

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
	super::onAnyStateChange(gameState);

	if (gameState->stateType == GameState::StateType::CardReplace || gameState->previousStateType == GameState::StateType::CardReplace)
	{
		LocalizedString* bannerString = Strings::Hexus_Banners_RemainingCardReplacements::create();
		ConstantString* cardReplacementsString = ConstantString::create(std::to_string(gameState->cardReplaceCount));

		bannerString->setStringReplacementVariables(cardReplacementsString);

		this->setBannerText(bannerString);
	}

	if (gameState->stateType == GameState::StateType::CardReplace)
	{
		if (gameState->cardReplaceCount > 0)
		{
			this->showBanner();

			this->penaltyIconParticles->start();
			this->penaltyIconParticles->setVisible(true);
		}
	}
	else if (gameState->previousStateType == GameState::StateType::CardReplace)
	{
		this->hideBanner();

		this->penaltyIconParticles->stop();
		this->penaltyIconParticles->setVisible(false);
	}
}
