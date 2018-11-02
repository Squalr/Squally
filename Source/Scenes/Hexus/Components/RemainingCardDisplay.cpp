#include "RemainingCardDisplay.h"

RemainingCardDisplay* RemainingCardDisplay::create()
{
	RemainingCardDisplay* instance = new RemainingCardDisplay();

	instance->autorelease();

	return instance;
}

RemainingCardDisplay::RemainingCardDisplay()
{
	this->remainingCardSprite = Sprite::create(Resources::Minigames_Hexus_RemainingCardsIcon);
	this->remainingCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->enemyRemainingCardSprite = Sprite::create(Resources::Minigames_Hexus_RemainingCardsIcon);
	this->enemyRemainingCardLabel = Label::create("", Localization::getCodingFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->remainingCardLabel->enableOutline(Color4B::BLACK, 4);
	this->remainingCardSprite->setOpacity(0);
	this->enemyRemainingCardLabel->enableOutline(Color4B::BLACK, 4);
	this->enemyRemainingCardSprite->setOpacity(0);

	this->remainingCardSprite->addChild(this->remainingCardLabel);
	this->addChild(this->remainingCardSprite);
	this->enemyRemainingCardSprite->addChild(this->enemyRemainingCardLabel);
	this->addChild(this->enemyRemainingCardSprite);
}

RemainingCardDisplay::~RemainingCardDisplay()
{
}

void RemainingCardDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->remainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY + 144.0f);
	this->remainingCardLabel->setPosition(Vec2(this->remainingCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));
	this->enemyRemainingCardSprite->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY - 144.0f);
	this->enemyRemainingCardLabel->setPosition(Vec2(this->enemyRemainingCardSprite->getContentSize().width / 2.0f + 16.0f, 16.0f));
}

void RemainingCardDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void RemainingCardDisplay::onStateChange(GameState* gameState)
{
	ComponentBase::onStateChange(gameState);

	this->remainingCardLabel->setString(std::to_string(gameState->playableCardsThisTurn));
	this->enemyRemainingCardLabel->setString(std::to_string(gameState->playableCardsThisTurn));

	switch (gameState->stateType)
	{
		case GameState::PlayerTurnStart:
		{
			if (!gameState->enemyLastStanded)
			{
				this->remainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::OpponentTurnStart:
		{
			if (!gameState->playerLastStanded)
			{
				this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 255));
			}

			break;
		}
		case GameState::TurnEnd:
		{
			this->remainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			this->enemyRemainingCardSprite->runAction(FadeTo::create(0.25f, 0));
			break;
		}
	}
}
