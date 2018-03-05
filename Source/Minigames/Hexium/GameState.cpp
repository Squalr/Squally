#include "GameState.h"

GameState* GameState::create()
{
	GameState* gameState = new GameState();

	gameState->autorelease();

	return gameState;
}

GameState::GameState()
{
	this->selectedCard = nullptr;
	this->updateStateCallback = nullptr;
	this->endTurnCallback = nullptr;
	this->cardPreviewCallback = nullptr;
	this->requestAiCallback = nullptr;

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
	this->playerHand->setRowWidth(Config::handWidth);
	this->enemyHand->setRowWidth(Config::enemyHandWidth);

	this->addChild(this->enemyGraveyard);
	this->addChild(this->enemyDeck);
	this->addChild(this->enemyHexCards);
	this->addChild(this->enemyDecimalCards);
	this->addChild(this->enemyBinaryCards);
	this->addChild(this->enemyHand);

	this->addChild(this->playerGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->playerHexCards);
	this->addChild(this->playerDecimalCards);
	this->addChild(this->playerBinaryCards);
	this->addChild(this->playerHand);
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

	this->enemyHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::handOffsetY + 256.0f);
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
	this->selectCard(card);
}

void GameState::selectCard(Card* card)
{
	if (this->selectedCard != nullptr)
	{
		this->selectedCard->stopAllActions();
		this->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->selectedCard->position));
	}

	this->selectedCard = card;

	if (this->selectedCard == nullptr)
	{
		return;
	}

	this->selectedCard->stopAllActions();
	this->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	switch (this->selectedCard->cardData->cardType)
	{
	case CardData::CardType::Binary:
		this->playerBinaryCards->enableRowSelection(CC_CALLBACK_0(GameState::playSelectedCard, this));
		break;
	case CardData::CardType::Decimal:
		this->playerDecimalCards->enableRowSelection(CC_CALLBACK_0(GameState::playSelectedCard, this));
		break;
	case CardData::CardType::Hexidecimal:
		this->playerHexCards->enableRowSelection(CC_CALLBACK_0(GameState::playSelectedCard, this));
		break;
	}
}

void GameState::cancelCurrentAction()
{
	if (this->selectedCard != nullptr)
	{
		switch (this->selectedCard->cardData->cardType)
		{
		case CardData::CardType::Binary:
			this->playerBinaryCards->disableRowSelection();
			break;
		case CardData::CardType::Decimal:
			this->playerDecimalCards->disableRowSelection();
			break;
		case CardData::CardType::Hexidecimal:
			this->playerHexCards->disableRowSelection();
			break;
		}

		this->selectCard(nullptr);
	}
}

void GameState::onRowCardClick(Card* card)
{
	// TODO: potentially store up xor/and/or targets if one is queued up
}

void GameState::playSelectedCard()
{
	if (this->selectedCard == nullptr)
	{
		return;
	}

	switch (this->selectedCard->cardData->cardType) {
	case CardData::CardType::Binary:
		this->playerHand->removeCard(this->selectedCard);
		this->playerBinaryCards->disableRowSelection();
		this->playerBinaryCards->insertCard(this->selectedCard, Config::insertDelay);
		this->endTurn();
		break;
	case CardData::CardType::Decimal:
		this->playerHand->removeCard(this->selectedCard);
		this->playerDecimalCards->disableRowSelection();
		this->playerDecimalCards->insertCard(this->selectedCard, Config::insertDelay);
		this->endTurn();
		break;
	case CardData::CardType::Hexidecimal:
		this->playerHand->removeCard(this->selectedCard);
		this->playerHexCards->disableRowSelection();
		this->playerHexCards->insertCard(this->selectedCard, Config::insertDelay);
		this->endTurn();
		break;
	}
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

	startPlayerDeck->copyTo(this->playerDeck);
	startEnemyDeck->copyTo(this->enemyDeck);

	// Draw starting cards
	int drawnCount = 0;

	while (playerDeck->hasCards() && drawnCount < Config::startingCardAmount)
	{
		playerHand->insertCard(this->playerDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	drawnCount = 0;

	while (enemyDeck->hasCards() && drawnCount < Config::startingCardAmount)
	{
		enemyHand->insertCard(this->enemyDeck->drawCard(), 0.0f);
		drawnCount++;
	}

	this->disableUserInteraction();

	this->randomizeTurn();
}

void GameState::randomizeTurn()
{
	if (RandomHelper::random_real(0.0f, 1.0f) > 0.5f)
	{
		this->turn = Turn::Player;
	}
	else
	{
		this->turn = Turn::Enemy;
	}

	this->runAction(Sequence::create(
		DelayTime::create(Config::turnAnimationDelay),
		CallFunc::create(CC_CALLBACK_0(GameState::drawCard, this)),
		nullptr
	));
}

void GameState::drawCard()
{
	switch (this->turn)
	{
	case Turn::Enemy:
	{
		if (!this->enemyDeck->hasCards())
		{
			this->giveControl();
			return;
		}

		// Simply insert the card directly into the enemy hand for the enemy
		enemyHand->insertCard(this->enemyDeck->drawCard(), 0.0f);

		this->updateState();

		this->runAction(Sequence::create(
			DelayTime::create(Config::enemyDrawDelay),
			CallFunc::create(CC_CALLBACK_0(GameState::giveControl, this)),
			nullptr
		));
		break;
	}
	case Turn::Player:
	default:
	{
		if (!this->playerDeck->hasCards())
		{
			this->giveControl();
			return;
		}

		Card * card = this->playerDeck->drawCard();
		CardRow * hand = this->playerHand;

		GameUtils::changeParent(card, this, true);

		this->updateState();

		this->runAction(Sequence::create(
			CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, card, Config::cardDrawDelay)),
			DelayTime::create(Config::cardDrawDelay),
			DelayTime::create(Config::revealDelay),
			CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, card, Config::insertDelay)),
			CallFunc::create(CC_CALLBACK_0(GameState::updateState, this)),
			DelayTime::create(Config::insertDelay),
			CallFunc::create(CC_CALLBACK_0(GameState::giveControl, this)),
			nullptr
		));

		break;
	}
	}
}

void GameState::giveControl()
{
	switch (this->turn)
	{
	case Turn::Enemy:
		if (this->requestAiCallback != nullptr) {
			this->requestAiCallback(this);
		}
		break;
	case Turn::Player:
	default:
		this->enableUserInteraction();
		break;
	}
}

void GameState::endTurn()
{
	float endTurnDelay = Config::endTurnDelay;

	switch (this->turn)
	{
	case Turn::Enemy:
		endTurnDelay = Config::enemyEndTurnDelay;
		this->turn = Turn::Player;
		break;
	case Turn::Player:
	default:
		this->disableUserInteraction();
		this->turn = Turn::Enemy;
		break;
	}

	this->runAction(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(GameState::updateState, this)),
		DelayTime::create(endTurnDelay),
		CallFunc::create(CC_CALLBACK_0(GameState::callEndTurn, this)),
		DelayTime::create(Config::betweenTurnDelay),
		CallFunc::create(CC_CALLBACK_0(GameState::drawCard, this)),
		nullptr
	));
}

void GameState::updateState()
{
	if (this->updateStateCallback != nullptr)
	{
		this->updateStateCallback(true);
	}
}

void GameState::callEndTurn()
{
	if (this->endTurnCallback != nullptr)
	{
		this->endTurnCallback();
	}
}

int GameState::getPlayerTotal()
{
	int total = 0;

	total += this->playerBinaryCards->getRowAttack();
	total += this->playerDecimalCards->getRowAttack();
	total += this->playerHexCards->getRowAttack();

	return total;
}

int GameState::getEnemyTotal()
{
	int total = 0;

	total += this->enemyBinaryCards->getRowAttack();
	total += this->enemyDecimalCards->getRowAttack();
	total += this->enemyHexCards->getRowAttack();

	return total;
}

void GameState::setCardPreviewCallback(std::function<void(Card*)> callback)
{
	this->cardPreviewCallback = callback;
}

void GameState::setUpdateStateCallback(std::function<void(bool)> callback)
{
	this->updateStateCallback = callback;
}

void GameState::setEndTurnCallback(std::function<void()> callback)
{
	this->endTurnCallback = callback;
}

void GameState::setRequestAiCallback(std::function<void(GameState*)> callback)
{
	this->requestAiCallback = callback;
}

void GameState::enableUserInteraction()
{
	this->playerHand->enableInteraction();
	this->playerBinaryCards->enableInteraction();
	this->playerDecimalCards->enableInteraction();
	this->playerHexCards->enableInteraction();
	this->enemyBinaryCards->enableInteraction();
	this->enemyDecimalCards->enableInteraction();
	this->enemyHexCards->enableInteraction();
}

void GameState::disableUserInteraction()
{
	this->playerHand->disableInteraction();
	this->playerBinaryCards->disableInteraction();
	this->playerDecimalCards->disableInteraction();
	this->playerHexCards->disableInteraction();
	this->enemyBinaryCards->disableInteraction();
	this->enemyDecimalCards->disableInteraction();
	this->enemyHexCards->disableInteraction();
}