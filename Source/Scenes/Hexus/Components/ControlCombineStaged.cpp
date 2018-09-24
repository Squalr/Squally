#include "ControlCombineStaged.h"

ControlCombineStaged* ControlCombineStaged::create()
{
	ControlCombineStaged* instance = new ControlCombineStaged();

	instance->autorelease();

	return instance;
}

ControlCombineStaged::ControlCombineStaged()
{
	this->combineStatus = Label::create("", Localization::getMainFont(), 28.0f);

	this->combineStatus->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->combineStatus->setTextColor(Color4B::WHITE);
	this->combineStatus->enableOutline(Color4B::BLACK, 2);
	this->combineStatus->setDimensions(Config::statusLabelWidth, 0.0f);
	this->combineStatus->setOpacity(0);

	this->cancelButton = MenuSprite::create(Resources::Menus_Buttons_CancelV2Button, Resources::Menus_Buttons_CancelV2ButtonHover, Resources::Menus_Buttons_CancelV2ButtonClick);
	this->cancelButton->setCascadeOpacityEnabled(true);
	this->cancelButton->setOpacity(0.0f);
	this->cancelButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->combineStatus);
	this->addChild(this->cancelButton);
}

ControlCombineStaged::~ControlCombineStaged()
{
}

void ControlCombineStaged::initializePositions()
{
	ComponentBase::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cancelButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->combineStatus->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter - Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
}

void ControlCombineStaged::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlCombineStaged) {
		switch (gameState->turn)
		{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			this->updateCombineStatus();
			break;
		case GameState::Turn::Enemy:
			this->aiPerformAction(gameState);
			break;
		}
	}
}

void ControlCombineStaged::initializeCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(ControlCombineStaged::onCombineCancel, this));

	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlCombineStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlCombineStaged::selectCard, this));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlCombineStaged::stageCombineTarget, this));
}

void ControlCombineStaged::aiPerformAction(GameState* gameState)
{
	this->activeGameState->enemyHand->removeCard(this->activeGameState->selectedCard);
	this->activeGameState->enemyGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

	// n^2 card compare to figure out the best strategy
	// Maybe there is some better way to do this calculation

	std::vector<Card*> cards = gameState->getEnemyCards(); // all valid source cards for the operation must be our own
	Card* bestSourceCard = nullptr;
	Card* bestTargetCard = nullptr;
	int bestDiff = INT_MIN;

	// First simulate buffing your own cards
	for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
	{
		Card* sourceCard = *sourceCardIterator;

		// First we iterate through only our own cards
		for (auto targetCardIterator = cards.begin(); targetCardIterator != cards.end(); targetCardIterator++)
		{
			if (sourceCardIterator == targetCardIterator) {
				continue; // we're not allowed to apply a card to itself
			}

			Card* targetCard = *targetCardIterator;
			Card::Operation operation = Card::toOperation(
				gameState->selectedCard->cardData->cardType, 
				sourceCard->getAttack()
			);

			int diff = targetCard->simulateOperation(operation);
			if (diff > bestDiff) {
				bestDiff = diff;
				bestSourceCard = sourceCard;
				bestTargetCard = targetCard;
			}
		}
	}

	// Then simulate attacking the player
	std::vector<Card*> playerCards = gameState->getPlayerCards();
	for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
	{
		Card* sourceCard = *sourceCardIterator;

		// This time we iterate through the players cards
		for (auto targetCardIterator = playerCards.begin(); targetCardIterator != playerCards.end(); targetCardIterator++)
		{
			if (sourceCardIterator == targetCardIterator) {
				continue; // we're not allowed to apply a card to itself
			}

			Card* targetCard = *targetCardIterator;
			Card::Operation operation = Card::toOperation(
				gameState->selectedCard->cardData->cardType, 
				sourceCard->getAttack()
			);

			// multiply by negative 1 to flip the diff because we want to hurt the player
			int diff = targetCard->simulateOperation(operation) * -1;
			if (diff > bestDiff) {
				bestDiff = diff;
				bestSourceCard = sourceCard;
				bestTargetCard = targetCard;
			}
		}
	}

	this->activeGameState->stagedCombineSourceCard = bestSourceCard;
	this->activeGameState->stagedCombineTargetCard = bestTargetCard;

	Card::Operation operation = Card::toOperation(
		this->activeGameState->selectedCard->cardData->cardType, 
		this->activeGameState->stagedCombineSourceCard->getAttack()
	);

	// NOTE, the future we may want destination card to be different than target
	Card* destinationCard = this->activeGameState->stagedCombineTargetCard;
	destinationCard->addOperation(operation);

	GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
}

void ControlCombineStaged::selectCard(Card* card)
{
	// Unstage/deselect card if clicking the active card
	if (card == this->activeGameState->selectedCard)
	{
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
		GameState::updateState(this->activeGameState, GameState::StateType::ControlNeutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
}


void ControlCombineStaged::stageCombineTarget(Card* card)
{
	// If we click a card that is already selected our source, deselect our source
	if (this->activeGameState->stagedCombineSourceCard == card) {
		card->unfocus();
		this->activeGameState->stagedCombineSourceCard = nullptr;
		this->updateCombineStatus();
		return;
	}

	// If we click a card that is already selected our destination, deselect our destination
	if (this->activeGameState->stagedCombineTargetCard == card) {
		card->unfocus();
		this->activeGameState->stagedCombineTargetCard = nullptr;
		this->updateCombineStatus();
		return;
	}

	// we assign the source card first, then the destination/target
	if (this->activeGameState->stagedCombineSourceCard == nullptr) {
		card->focus();
		this->activeGameState->stagedCombineSourceCard = card;
		this->updateCombineStatus();
	}
	else {
		card->focus();
		this->activeGameState->stagedCombineTargetCard = card;
		this->updateCombineStatus();
	}

	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		if (this->activeGameState->stagedCombineSourceCard != nullptr && this->activeGameState->stagedCombineTargetCard != nullptr)
		{
			this->activeGameState->stagedCombineSourceCard->unfocus();
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

			Card::Operation operation = Card::toOperation(this->activeGameState->selectedCard->cardData->cardType, this->activeGameState->stagedCombineSourceCard->getAttack());

			// NOTE, the future we may want destination card to be different than target
			Card* destinationCard = this->activeGameState->stagedCombineTargetCard;
			destinationCard->addOperation(operation);

			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		}
		break;
	}
}

void ControlCombineStaged::onCombineCancel(MenuSprite* menuSprite)
{
	// Deselect current card (by selecting the selected card)
	this->selectCard(this->activeGameState->selectedCard);

	this->updateCombineStatus();
}

void ControlCombineStaged::updateCombineStatus()
{
	if (this->activeGameState->turn != GameState::Turn::Player)
	{
		return;
	}
	
	if (this->activeGameState->stagedCombineSourceCard == nullptr) {
		this->combineStatus->setString("Choose the source card for your operation");
		this->combineStatus->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
	else if (this->activeGameState->stagedCombineTargetCard == nullptr) {
		this->combineStatus->setString("Choose the target/destination card for your operation");
		this->combineStatus->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
	else {
		this->combineStatus->runAction(FadeTo::create(0.25f, 0));
		this->cancelButton->runAction(FadeTo::create(0.25f, 0));
	}
}
