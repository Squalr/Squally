#include "RemainingCardDisplay.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCParticleSystemQuad.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"
#include "Resources/ParticleResources.h"

#include "Strings/Hexus/CardsToPlayToolTip.h"
#include "Strings/Generics/Constant.h"
#include "Strings/Generics/Infinity.h"

using namespace cocos2d;

RemainingCardDisplay* RemainingCardDisplay::create()
{
	RemainingCardDisplay* instance = new RemainingCardDisplay();

	instance->autorelease();

	return instance;
}

RemainingCardDisplay::RemainingCardDisplay()
{
	this->particles = ParticleSystemQuad::create(ParticleResources::Hexus_BlueAura);
	this->remainingCardSprite = ClickableNode::create(HexusResources::RemainingCardsIcon, HexusResources::RemainingCardsIcon);
	this->remainingCardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());
	this->enemyRemainingCardSprite = Sprite::create(HexusResources::RemainingCardsIcon);
	this->enemyRemainingCardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());

	this->remainingCardMouseOverPanel = LayerColor::create(Color4B::BLACK, 320.0f, 96.0f);
	this->remainingCardMouseOverLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_CardsToPlayToolTip::create());

	this->remainingCardMouseOverLabel->setDimensions(320.0f - 16.0f, 0.0f);

	this->remainingCardLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyRemainingCardLabel->enableOutline(Color4B::BLACK, 4);

	this->remainingCardSprite->addChild(this->remainingCardLabel);
	this->addChild(this->particles);
	this->addChild(this->remainingCardSprite);
	this->enemyRemainingCardSprite->addChild(this->enemyRemainingCardLabel);
	this->addChild(this->enemyRemainingCardSprite);
	this->addChild(this->remainingCardMouseOverPanel);
	this->addChild(this->remainingCardMouseOverLabel);
}

RemainingCardDisplay::~RemainingCardDisplay()
{
}

void RemainingCardDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->remainingCardMouseOverPanel->setOpacity(0);
	this->remainingCardMouseOverLabel->setOpacity(0);
	this->particles->setVisible(false);
	this->remainingCardSprite->setOpacity(0);
	this->enemyRemainingCardSprite->setOpacity(0);
}

void RemainingCardDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float spriteOffsetY = 144.0f;

	this->particles->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY);
	this->remainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY);
	this->remainingCardLabel->setPosition(Vec2(16.0f, -this->remainingCardSprite->getContentSize().height / 2.0f + 16.0f));
	this->enemyRemainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - spriteOffsetY);
	this->enemyRemainingCardLabel->setPosition(Vec2(this->enemyRemainingCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));

	this->remainingCardMouseOverPanel->setPosition(
		visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX - this->remainingCardMouseOverPanel->getContentSize().width / 2.0f,
		visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY - this->remainingCardMouseOverPanel->getContentSize().height / 2.0 + 96.0f
	);
	this->remainingCardMouseOverLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + spriteOffsetY + 96.0f);
}

void RemainingCardDisplay::onRemaningCardDisplayMouseOver()
{
	this->remainingCardMouseOverPanel->setOpacity(196);
	this->remainingCardMouseOverLabel->setOpacity(255);
}

void RemainingCardDisplay::onRemaningCardDisplayMouseOut()
{
	this->remainingCardMouseOverPanel->setOpacity(0);
	this->remainingCardMouseOverLabel->setOpacity(0);
}

void RemainingCardDisplay::enableCardDisplayInteraction()
{
	this->particles->setVisible(true);
	this->remainingCardSprite->setMouseOverCallback(CC_CALLBACK_0(RemainingCardDisplay::onRemaningCardDisplayMouseOver, this));
	this->remainingCardSprite->setMouseOutCallback(CC_CALLBACK_0(RemainingCardDisplay::onRemaningCardDisplayMouseOut, this));
}

void RemainingCardDisplay::disableCardDisplayInteraction()
{
	this->particles->setVisible(false);
	this->remainingCardSprite->setMouseOverCallback(nullptr);
	this->remainingCardSprite->setMouseOutCallback(nullptr);
	this->onRemaningCardDisplayMouseOut();
}

void RemainingCardDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void RemainingCardDisplay::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	if (gameState->enemyPassed || gameState->playerPassed)
	{
		this->remainingCardLabel->setStringReplacementVariables(Strings::Generics_Infinity::create());
		this->enemyRemainingCardLabel->setStringReplacementVariables(Strings::Generics_Infinity::create());
	}
	else
	{
		this->remainingCardLabel->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playableCardsThisTurn)));
		this->enemyRemainingCardLabel->setStringReplacementVariables(ConstantString::create(std::to_string(gameState->playableCardsThisTurn)));
	}

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->enemyRemainingCardLabel->setStringReplacementVariables(ConstantString::create(std::to_string(0)));
			break;
		}
		case GameState::Turn::Enemy:
		{
			this->remainingCardLabel->setStringReplacementVariables(ConstantString::create(std::to_string(0)));
			break;
		}
		default:
		{
			break;
		}
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::Neutral:
		case GameState::StateType::SelectionStaged:
		case GameState::StateType::CombineStaged:
		{
			this->enableCardDisplayInteraction();

			break;
		}
		default:
		{
			this->disableCardDisplayInteraction();

			break;
		}
	}

	switch (gameState->stateType)
	{
		case GameState::StateType::PlayerTurnStart:
		{
			this->remainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			break;
		}
		case GameState::StateType::OpponentTurnStart:
		{
			this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			break;
		}
		case GameState::StateType::TurnEnd:
		{
			//this->remainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			break;
		}
		default:
		{
			break;
		}
	}
}
