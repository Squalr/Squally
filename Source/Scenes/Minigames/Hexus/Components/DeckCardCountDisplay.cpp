#include "DeckCardCountDisplay.h"

DeckCardCountDisplay* DeckCardCountDisplay::create()
{
	DeckCardCountDisplay* deckCardCountDisplay = new DeckCardCountDisplay();

	deckCardCountDisplay->autorelease();

	return deckCardCountDisplay;
}

DeckCardCountDisplay::DeckCardCountDisplay()
{
	this->playerDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->playerDeckCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->playerDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->enemyDeckCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->enemyDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->playerDeckCardCountFrame);
	this->addChild(this->playerDeckCardCountText);
	this->addChild(this->enemyDeckCardCountFrame);
	this->addChild(this->enemyDeckCardCountText);
}

DeckCardCountDisplay::~DeckCardCountDisplay()
{
}

void DeckCardCountDisplay::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void DeckCardCountDisplay::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY - 32.0f);
	this->playerDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY);

	this->enemyDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY);
	this->enemyDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY + 32.0f);
}

void DeckCardCountDisplay::initializeListeners()
{
}

void DeckCardCountDisplay::onStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
}

void DeckCardCountDisplay::updateTotals(GameState* gameState)
{
	this->playerDeckCardCountText->setString(StrUtils::toStringZeroPad(gameState->playerDeck->getCardCount(), 2));
	this->enemyDeckCardCountText->setString(StrUtils::toStringZeroPad(gameState->enemyDeck->getCardCount(), 2));
}
