#include "Hexus.h"

Hexus* Hexus::create()
{
	Hexus* instance = new Hexus();

	instance->autorelease();

	return instance;
}

Hexus::Hexus()
{
	this->gameBackground = Sprite::create(Resources::Minigames_Hexus_Gameboard);
	this->gameState = GameState::create();
	this->avatars = Avatars::create();
	this->banners = Banners::create();
	this->cardPreview = CardPreview::create();
	this->controlDraw = ControlDraw::create();
	this->controlNeutral = ControlNeutral::create();
	this->controlEndTurn = ControlEndTurn::create();
	this->controlSacrificeStaged = ControlSacrificeStaged::create();
	this->controlCombineStaged = ControlCombineStaged::create();
	this->controlSelectionStaged = ControlSelectionStaged::create();
	this->controlReplaceCards = ControlReplaceCards::create();
	this->controlGameEnd = ControlGameEnd::create();
	this->coinFlip = CoinFlip::create();
	this->deckCardCountDisplay = DeckCardCountDisplay::create();
	this->handCardCountDisplay = HandCardCountDisplay::create();
	this->lossesDisplay = LossesDisplay::create();
	this->passButton = PassButton::create();
	this->rowTotals = RowTotals::create();
	this->scoreTotal = ScoreTotal::create();

	this->addChild(this->gameBackground);
	this->addChild(this->gameState);
	this->addChild(this->avatars);
	this->addChild(this->controlDraw);
	this->addChild(this->controlNeutral);
	this->addChild(this->controlSelectionStaged);
	this->addChild(this->controlSacrificeStaged);
	this->addChild(this->controlCombineStaged);
	this->addChild(this->controlEndTurn);
	this->addChild(this->cardPreview);
	this->addChild(this->lossesDisplay);
	this->addChild(this->passButton);
	this->addChild(this->deckCardCountDisplay);
	this->addChild(this->handCardCountDisplay);
	this->addChild(this->rowTotals);
	this->addChild(this->scoreTotal);
	this->addChild(this->controlReplaceCards);
	this->addChild(this->controlGameEnd);
	this->addChild(this->coinFlip);
	this->addChild(this->banners);
	this->addChild(Mouse::create());
}

Hexus::~Hexus()
{
}

void Hexus::onEnter()
{
	FadeScene::onEnter();

	SoundManager::playMusicResource(Resources::Music_LastMarch);

	GameState::updateState(this->gameState, GameState::StateType::RoundStart);
}

void Hexus::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
}

void Hexus::initializeListeners()
{
	FadeScene::initializeListeners();
	
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Hexus::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Hexus::onGameStart(EventCustom* eventCustom)
{
	HexusEvents::HexusGameEventArgs* args = (HexusEvents::HexusGameEventArgs*)(eventCustom->getUserData());

	this->avatars->initializeEnemyAvatar(args->opponentData);

	this->gameState->onGameEndCallback = args->onGameEndCallback;
	this->gameState->opponentData = args->opponentData;

	this->gameState->previousStateType = GameState::StateType::EmptyState;
	this->gameState->stateType = GameState::StateType::EmptyState;
	this->gameState->playerLosses = 0;
	this->gameState->enemyLosses = 0;
	this->gameState->cardReplaceCount = 3;

	this->gameState->playerBinaryCards->clear();
	this->gameState->playerDecimalCards->clear();
	this->gameState->playerHexCards->clear();

	this->gameState->enemyBinaryCards->clear();
	this->gameState->enemyDecimalCards->clear();
	this->gameState->enemyHexCards->clear();

	this->gameState->playerGraveyard->clear();
	this->gameState->enemyGraveyard->clear();
	this->gameState->playerHand->clear();
	this->gameState->enemyHand->clear();
	this->gameState->playerDeck->clear();
	this->gameState->enemyDeck->clear();

	args->opponentData->getDeck()->copyTo(this->gameState->enemyDeck);
	Deck::create(Card::CardStyle::Earth, CardStorage::getInstance()->getDeckCards())->copyTo(this->gameState->playerDeck);

	NavigationEvents::navigate(NavigationEvents::GameScreen::Hexus);
}

void Hexus::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isRunning() || !this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			//this->gameState->cancelCurrentAction(true);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(true, this->gameState->opponentData));
			break;
		default:
			break;
	}
}

void Hexus::onClose(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
