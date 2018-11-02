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

	gameState = gameState;

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->initializeCallbacks(gameState);
			this->updateCombineStatus(gameState);
			break;
		}
		default:
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

	this->updateCombineStatus(gameState);
}

void StateCombineStaged::initializeCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(StateCombineStaged::onCombineCancel, this, gameState));

	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this, gameState));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
}

void StateCombineStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedCard)
	{
		gameState->stagedCombineSourceCard = nullptr;
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));
		gameState->selectedCard = nullptr;

		GameState::updateState(gameState, GameState::StateType::Neutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	gameState->selectedCard->stopAllActions();
	gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));

	gameState->selectedCard = card;
	gameState->selectedCard->stopAllActions();
	gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(gameState, GameState::StateType::SelectionStaged);
}


void StateCombineStaged::stageCombineTarget(Card* card, GameState* gameState)
{
	// If we click a card that is already selected our source, deselect our source
	if (gameState->stagedCombineSourceCard == card)
	{
		card->unfocus();
		gameState->stagedCombineSourceCard = nullptr;
		this->updateCombineStatus(gameState);
		return;
	}

	// If we click a card that is already selected our destination, deselect our destination
	if (gameState->stagedCombineTargetCard == card)
	{
		card->unfocus();
		gameState->stagedCombineTargetCard = nullptr;
		this->updateCombineStatus(gameState);
		return;
	}

	// we assign the source card first, then the destination/target
	if (gameState->stagedCombineSourceCard == nullptr)
	{
		card->focus();
		gameState->stagedCombineSourceCard = card;
		this->updateCombineStatus(gameState);
	}
	else
	{
		card->focus();
		gameState->stagedCombineTargetCard = card;
		this->updateCombineStatus(gameState);
	}

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		{
			if (gameState->stagedCombineSourceCard != nullptr && gameState->stagedCombineTargetCard != nullptr)
			{
				gameState->stagedCombineSourceCard->unfocus();
				this->updateCombineStatus(gameState);

				GameState::updateState(gameState, GameState::StateType::PlayCard);
			}
			break;
		}
		default:
			break;
	}
}

void StateCombineStaged::onCombineCancel(MenuSprite* menuSprite, GameState* gameState)
{
	// Deselect current card (by selecting the selected card)
	this->selectCard(gameState->selectedCard, gameState);

	this->updateCombineStatus(gameState);
}

void StateCombineStaged::updateCombineStatus(GameState* gameState)
{
	if (gameState->turn != GameState::Turn::Player)
	{
		return;
	}

	if (gameState->stateType == GameState::StateType::CombineStaged && gameState->stagedCombineSourceCard == nullptr)
	{
		this->combineStatus->setString("Choose the source card for your operation");
		this->combineStatus->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
	else if (gameState->stateType == GameState::StateType::CombineStaged && gameState->stagedCombineTargetCard == nullptr)
	{
		this->combineStatus->setString("Choose the target card for your operation");
		this->combineStatus->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
	else
	{
		this->combineStatus->runAction(FadeTo::create(0.25f, 0));
		this->cancelButton->runAction(FadeTo::create(0.25f, 0));
	}
}
