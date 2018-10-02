#include "StateCombineStaged.h"

StateCombineStaged* StateCombineStaged::create()
{
	StateCombineStaged* instance = new StateCombineStaged();

	instance->autorelease();

	return instance;
}

StateCombineStaged::StateCombineStaged() : StateBase(GameState::StateType::CombineStaged)
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

StateCombineStaged::~StateCombineStaged()
{
}

void StateCombineStaged::initializePositions()
{
	StateBase::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cancelButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->combineStatus->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter - Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
}

void StateCombineStaged::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateCombineStaged::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->activeGameState = gameState;

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

void StateCombineStaged::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateCombineStaged::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateCombineStaged::initializeCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(StateCombineStaged::onCombineCancel, this));

	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this));
}

void StateCombineStaged::aiPerformAction(GameState* gameState)
{
	this->activeGameState->enemyHand->removeCard(this->activeGameState->selectedCard);
	this->activeGameState->enemyGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

	Card::Operation operation = Card::toOperation(
		this->activeGameState->selectedCard->cardData->cardType, 
		this->activeGameState->stagedCombineSourceCard->getAttack()
	);

	// NOTE, the future we may want destination card to be different than target
	Card* destinationCard = this->activeGameState->stagedCombineTargetCard;
	destinationCard->addOperation(operation);
	SoundManager::playSoundResource(Resources::Sounds_Hexus_Attacks_05_Acid_Spell);

	GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
}

void StateCombineStaged::selectCard(Card* card)
{
	// Unstage/deselect card if clicking the active card
	if (card == this->activeGameState->selectedCard)
	{
		this->activeGameState->stagedCombineSourceCard = nullptr;
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
		this->activeGameState->selectedCard = nullptr;
		GameState::updateState(this->activeGameState, GameState::StateType::Neutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(this->activeGameState, GameState::StateType::SelectionStaged);
}


void StateCombineStaged::stageCombineTarget(Card* card)
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
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Attacks_05_Acid_Spell);

			GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
		}
		break;
	}
}

void StateCombineStaged::onCombineCancel(MenuSprite* menuSprite)
{
	// Deselect current card (by selecting the selected card)
	this->selectCard(this->activeGameState->selectedCard);

	this->updateCombineStatus();
}

void StateCombineStaged::updateCombineStatus()
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
