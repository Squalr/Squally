#include "GameState.h"

GameState* GameState::create()
{
	GameState* gameState = new GameState();

	gameState->autorelease();

	return gameState;
}

GameState::GameState()
{
	this->updateStateCallback = nullptr;
	this->cardPreviewCallback = nullptr;

	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create();
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create();
	this->playerDecimalCards = CardRow::create();
	this->playerHexCards = CardRow::create();

	this->enemyDeck = Deck::create();
	this->enemyHand = CardRow::create();
	this->enemyGraveyard = Deck::create();
	this->enemyBinaryCards = CardRow::create();
	this->enemyDecimalCards = CardRow::create();
	this->enemyHexCards = CardRow::create();

	this->enemyHand->setVisible(false);

	this->addChild(this->playerGraveyard);
	this->addChild(this->enemyGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->playerBinaryCards);
	this->addChild(this->playerDecimalCards);
	this->addChild(this->playerHexCards);

	this->addChild(this->enemyDeck);
	this->addChild(this->playerHand);
	this->addChild(this->enemyHand);
	this->addChild(this->enemyBinaryCards);
	this->addChild(this->enemyDecimalCards);
	this->addChild(this->enemyHexCards);
}

GameState::~GameState()
{
}

void GameState::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void GameState::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::graveyardOffsetY);
	this->playerGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::graveyardOffsetY);

	this->playerDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY);
	this->enemyDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY);

	this->playerHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY);
	this->playerBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::handOffsetY);
	this->enemyBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);

}

void GameState::initializeListeners()
{
	this->playerHand->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));
	this->enemyHand->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));

	this->playerBinaryCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));
	this->playerDecimalCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));
	this->playerHexCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));

	this->enemyBinaryCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));
	this->enemyDecimalCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));
	this->enemyHexCards->setMouseOverCallback(CC_CALLBACK_1(GameState::onCardMouseOver, this));

	this->playerHand->setMouseClickCallback(CC_CALLBACK_1(GameState::onHandCardClick, this));
	this->enemyHand->setMouseClickCallback(CC_CALLBACK_1(GameState::onHandCardClick, this));

	this->playerBinaryCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));
	this->playerDecimalCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));
	this->playerHexCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));

	this->enemyBinaryCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));
	this->enemyDecimalCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));
	this->enemyHexCards->setMouseClickCallback(CC_CALLBACK_1(GameState::onRowCardClick, this));
}


void GameState::onCardMouseOver(Card* card)
{
	if (this->cardPreviewCallback != nullptr)
	{
		this->cardPreviewCallback(card);
	}
}

void GameState::onHandCardClick(Card* card)
{
	switch (card->cardData->cardType) {
	case CardData::CardType::Binary:
		this->playerHand->removeCard(card);
		this->playerBinaryCards->insertCard(card, CardRow::standardInsertDelay);
		this->endTurn();
		break;
	case CardData::CardType::Decimal:
		this->playerHand->removeCard(card);
		this->playerDecimalCards->insertCard(card, CardRow::standardInsertDelay);
		this->endTurn();
		break;
	case CardData::CardType::Hexidecimal:
		this->playerHand->removeCard(card);
		this->playerHexCards->insertCard(card, CardRow::standardInsertDelay);
		this->endTurn();
		break;
	}
}

void GameState::onRowCardClick(Card* card)
{

}

void GameState::gameStart(Deck* startPlayerDeck, Deck* startEnemyDeck)
{
	this->playerLosses = 0;
	this->enemyLosses = 0;

	this->playerGraveyard->clear();
	this->enemyGraveyard->clear();
	this->playerHand->clear();
	this->enemyHand->clear();
	this->playerDeck->clear();
	this->enemyDeck->clear();

	this->playerDeck = startPlayerDeck;
	this->enemyDeck = startEnemyDeck;

	// Draw starting cards
	const int initialCardCount = 15;
	int drawnCount = 0;

	while (playerDeck->hasCards() && drawnCount < initialCardCount)
	{
		playerHand->insertCard(this->playerDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	drawnCount = 0;

	while (enemyDeck->hasCards() && drawnCount < initialCardCount)
	{
		enemyHand->insertCard(this->enemyDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	if (this->updateStateCallback != nullptr) {
		this->updateStateCallback(false);
	}

	this->randomizeTurn();
}

void GameState::randomizeTurn()
{
	const float turnAnimationDelay = 2.0f;

	if (RandomHelper::random_real(0.0f, 1.0f) > 0.5f)
	{
		this->turn = Turn::Player;
	}
	else
	{
		this->turn = Turn::Enemy;
	}

	// TEMP DEBUG:
	this->turn = Turn::Player;

	this->runAction(Sequence::create(
		DelayTime::create(turnAnimationDelay),
		CallFunc::create(CC_CALLBACK_0(GameState::drawCard, this)),
		nullptr
	));
}

void GameState::drawCard()
{
	switch (this->turn)
	{
	case Turn::Enemy:
		if (!this->enemyDeck->hasCards())
		{
			this->giveControl();
			return;
		}
		break;
	case Turn::Player:
	default:
		if (!this->playerDeck->hasCards())
		{
			this->giveControl();
			return;
		}
		break;
	}

	switch (this->turn)
	{
	case Turn::Enemy:
		// Simply insert the card directly into the enemy hand for the enemy
		enemyHand->insertCard(this->enemyDeck->drawCard(), 0.0f);

		if (this->updateStateCallback != nullptr) {
			this->updateStateCallback(false);
		}

		this->giveControl();
		break;
	case Turn::Player:
	default:
		Card * card = this->playerDeck->drawCard();
		CardRow * hand = this->playerHand;
		float cardDrawDelay = 0.75f;
		float revealDelay = 0.25f;
		float cardInsertDelay = CardRow::standardInsertDelay;

		GameUtils::changeParent(card, this, true);

		if (this->updateStateCallback != nullptr) {
			this->updateStateCallback(true);
		}

		this->runAction(Sequence::create(
			CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, card, cardDrawDelay)),
			DelayTime::create(cardDrawDelay),
			DelayTime::create(revealDelay),
			CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, card, cardInsertDelay)),
			DelayTime::create(cardInsertDelay),
			CallFunc::create(CC_CALLBACK_0(GameState::giveControl, this)),
			nullptr
		));
		break;
	}
}

void GameState::giveControl()
{
	switch (this->turn)
	{
	case Turn::Enemy:
		break;
	case Turn::Player:
	default:
		break;
	}
}

void GameState::endTurn()
{
	switch (this->turn)
	{
	case Turn::Enemy:
		this->turn = Turn::Player;
		break;
	case Turn::Player:
	default:
		this->turn = Turn::Enemy;
		break;
	}

	const float endTurnDelay = 0.25f;

	this->runAction(Sequence::create(
		DelayTime::create(endTurnDelay),
		CallFunc::create(CC_CALLBACK_0(GameState::drawCard, this)),
		nullptr
	));
}

void GameState::setCardPreviewCallback(std::function<void(Card*)> callback)
{
	this->cardPreviewCallback = callback;
}

void GameState::setUpdateStateCallback(std::function<void(bool)> callback)
{
	this->updateStateCallback = callback;
}
