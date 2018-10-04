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
	this->cardReplaceBanner = CardReplaceBanner::create();
	this->opponentFirstBanner = OpponentFirstBanner::create();
	this->opponentTurnBanner = OpponentTurnBanner::create();
	this->playerFirstBanner = PlayerFirstBanner::create();
	this->playerTurnBanner = PlayerTurnBanner::create();
	this->roundBanner = RoundBanner::create();
	this->victoryBanner = VictoryBanner::create();
	this->defeatBanner = DefeatBanner::create();
	this->cardPreview = CardPreview::create();
	this->stateAIDecideCard = StateAIDecideCard::create();
	this->stateAIDecideCardReplace = StateAIDecideCardReplace::create();
	this->stateAIDecidePass = StateAIDecidePass::create();
	this->stateCardReplace = StateCardReplace::create();
	this->stateCoinFlip = StateCoinFlip::create();
	this->stateCombineStaged = StateCombineStaged::create();
	this->stateDraw = StateDraw::create();
	this->stateDrawInitial = StateDrawInitial::create();
	this->stateGameEnd = StateGameEnd::create();
	this->stateGameStart = StateGameStart::create();
	this->stateNeutral = StateNeutral::create();
	this->stateOpponentTurnStart = StateOpponentTurnStart::create();
	this->statePass = StatePass::create();
	this->statePlayCard = StatePlayCard::create();
	this->statePlayCombineCard = StatePlayCombineCard::create();
	this->statePlayerTurnStart = StatePlayerTurnStart::create();
	this->stateRoundEnd = StateRoundEnd::create();
	this->stateRoundStart = StateRoundStart::create();
	this->stateSelectionStaged = StateSelectionStaged::create();
	this->stateTurnEnd = StateTurnEnd::create();
	this->deckCardCountDisplay = DeckCardCountDisplay::create();
	this->handCardCountDisplay = HandCardCountDisplay::create();
	this->lossesDisplay = LossesDisplay::create();
	this->passIndicators = PassIndicators::create();
	this->rowTotals = RowTotals::create();
	this->scoreTotal = ScoreTotal::create();
	this->debugDisplay = DebugDisplay::create();

	this->addChild(this->gameBackground);
	this->addChild(this->gameState);
	this->addChild(this->avatars);
	this->addChild(this->cardPreview);
	this->addChild(this->lossesDisplay);
	this->addChild(this->passIndicators);
	this->addChild(this->deckCardCountDisplay);
	this->addChild(this->handCardCountDisplay);
	this->addChild(this->rowTotals);
	this->addChild(this->scoreTotal);
	this->addChild(this->stateAIDecideCard);
	this->addChild(this->stateAIDecideCardReplace);
	this->addChild(this->stateAIDecidePass);
	this->addChild(this->stateCardReplace);
	this->addChild(this->stateCoinFlip);
	this->addChild(this->stateCombineStaged);
	this->addChild(this->stateDraw);
	this->addChild(this->stateDrawInitial);
	this->addChild(this->stateGameEnd);
	this->addChild(this->stateGameStart);
	this->addChild(this->stateNeutral);
	this->addChild(this->stateOpponentTurnStart);
	this->addChild(this->statePass);
	this->addChild(this->statePlayCard);
	this->addChild(this->statePlayCombineCard);
	this->addChild(this->statePlayerTurnStart);
	this->addChild(this->stateRoundEnd);
	this->addChild(this->stateRoundStart);
	this->addChild(this->stateSelectionStaged);
	this->addChild(this->stateTurnEnd);
	this->addChild(this->debugDisplay);
	this->addChild(this->cardReplaceBanner);
	this->addChild(this->opponentFirstBanner);
	this->addChild(this->opponentTurnBanner);
	this->addChild(this->playerFirstBanner);
	this->addChild(this->playerTurnBanner);
	this->addChild(this->roundBanner);
	this->addChild(this->victoryBanner);
	this->addChild(this->defeatBanner);
	this->addChild(Mouse::create());
}

Hexus::~Hexus()
{
}

void Hexus::onEnter()
{
	FadeScene::onEnter();

	SoundManager::playMusicResource(Resources::Music_LastMarch);

	if (this->gameState->stateType == GameState::StateType::EmptyState)
	{
		GameState::updateState(this->gameState, GameState::StateType::GameStart);
	}
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
	this->gameState->cardReplaceCount = 0;
	this->gameState->roundNumber = 0;
	this->gameState->turnNumber = 0;

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
			// NavigationEvents::navigate(NavigationEvents::GameScreen::Pause);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			// this->gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(true, this->gameState->opponentData));
			break;
		default:
			break;
	}
}

void Hexus::onClose(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
