#include "Hexus.h"

Hexus* Hexus::create()
{
	Hexus* instance = new Hexus();

	instance->autorelease();

	return instance;
}

Hexus::Hexus()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground = Sprite::create(Resources::Minigames_Hexus_Gameboard);
	this->gameState = GameState::create();
	this->avatars = Avatars::create();
	this->cardReplaceBanner = CardReplaceBanner::create();
	this->opponentFirstBanner = OpponentFirstBanner::create();
	this->opponentLastStandBanner = OpponentLastStandBanner::create();
	this->opponentPassBanner = OpponentPassBanner::create();
	this->opponentRoundWinBanner = OpponentRoundWinBanner::create();
	this->opponentTurnBanner = OpponentTurnBanner::create();
	this->playerFirstBanner = PlayerFirstBanner::create();
	this->playerLastStandBanner = PlayerLastStandBanner::create();
	this->playerPassBanner = PlayerPassBanner::create();
	this->playerRoundWinBanner = PlayerRoundWinBanner::create();
	this->playerTurnBanner = PlayerTurnBanner::create();
	this->roundBanner = RoundBanner::create();
	this->roundTieBanner = RoundTieBanner::create();
	this->victoryBanner = VictoryBanner::create();
	this->defeatBanner = DefeatBanner::create();
	this->drawBanner = DrawBanner::create();
	this->cardPreview = CardPreview::create();
	this->stagingHelperText = StagingHelperText::create();
	this->stateAIDecideCard = StateAIDecideCard::create();
	this->stateAIDecideCardReplace = StateAIDecideCardReplace::create();
	this->stateAIDecidePass = StateAIDecidePass::create();
	this->stateAIDecideTarget = StateAIDecideTarget::create();
	this->stateCardReplace = StateCardReplace::create();
	this->stateCoinFlip = StateCoinFlip::create();
	this->stateCombineStaged = StateCombineStaged::create();
	this->stateDraw = StateDraw::create();
	this->stateDrawInitial = StateDrawInitial::create();
	this->stateGameEnd = StateGameEnd::create();
	this->stateGameStart = StateGameStart::create();
	this->stateLoadInitialState = StateLoadInitialState::create();
	this->stateNeutral = StateNeutral::create();
	this->stateOpponentTurnStart = StateOpponentTurnStart::create();
	this->statePass = StatePass::create();
	this->statePlayCard = StatePlayCard::create();
	this->statePlayerTurnStart = StatePlayerTurnStart::create();
	this->stateRoundEnd = StateRoundEnd::create();
	this->stateRoundStart = StateRoundStart::create();
	this->stateSelectionStaged = StateSelectionStaged::create();
	this->stateTurnEnd = StateTurnEnd::create();
	this->stateTutorial = StateTutorial::create();
	this->deckCardCountDisplay = DeckCardCountDisplay::create();
	this->handCardCountDisplay = HandCardCountDisplay::create();
	this->drawCountDisplay = DrawCountDisplay::create();
	this->remainingCardDisplay = RemainingCardDisplay::create();
	this->lossesDisplay = LossesDisplay::create();
	this->rowTotals = RowTotals::create();
	this->scoreTotal = ScoreTotal::create();
	this->debugDisplay = DebugDisplay::create();
	this->tutorialAIntroSequence = TutorialAIntroSequence::create();
	this->tutorialAVictory = TutorialAVictory::create();
	this->tutorialAWinningRound = TutorialAWinningRound::create();
	this->pauseMenu = PauseMenu::create();
	this->optionsMenu = OptionsMenu::create();
	this->confirmationMenu = ConfirmationMenu::create();
	this->menuBackDrop = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);

	// Set up node pointers to be focused in tutorials -- a little hacky but avoids a cyclic dependency / refactor
	this->gameState->lossesDisplayPointer = this->lossesDisplay;
	this->gameState->playerBinaryRowTotalPointer = this->rowTotals->playerBinaryTotalSocket;
	this->gameState->playerDecimalRowTotalPointer = this->rowTotals->playerDecimalTotalSocket;
	this->gameState->playerHexRowTotalPointer = this->rowTotals->playerHexTotalSocket;
	this->gameState->enemyBinaryRowTotalPointer = this->rowTotals->enemyBinaryTotalSocket;
	this->gameState->enemyDecimalRowTotalPointer = this->rowTotals->enemyDecimalTotalSocket;
	this->gameState->enemyHexRowTotalPointer = this->rowTotals->enemyHexTotalSocket;
	this->gameState->scoreTotalPointer = this->scoreTotal;
	this->gameState->deckCardCountDisplayPointer = this->deckCardCountDisplay;
	this->gameState->handCardCountDisplayPointer = this->handCardCountDisplay;
	this->gameState->remainingCardDisplayPointer = this->remainingCardDisplay;
	this->gameState->drawCountDisplayPointer = this->drawCountDisplay;

	this->addChild(this->gameBackground);
	this->addChild(this->gameState);
	this->addChild(this->avatars);
	this->addChild(this->cardPreview);
	this->addChild(this->stagingHelperText);
	this->addChild(this->lossesDisplay);
	this->addChild(this->deckCardCountDisplay);
	this->addChild(this->handCardCountDisplay);
	this->addChild(this->remainingCardDisplay);
	this->addChild(this->drawCountDisplay);
	this->addChild(this->rowTotals);
	this->addChild(this->scoreTotal);
	this->addChild(this->stateAIDecideCard);
	this->addChild(this->stateAIDecideCardReplace);
	this->addChild(this->stateAIDecidePass);
	this->addChild(this->stateAIDecideTarget);
	this->addChild(this->stateCardReplace);
	this->addChild(this->stateCoinFlip);
	this->addChild(this->stateCombineStaged);
	this->addChild(this->stateDraw);
	this->addChild(this->stateDrawInitial);
	this->addChild(this->stateGameEnd);
	this->addChild(this->stateGameStart);
	this->addChild(this->stateLoadInitialState);
	this->addChild(this->stateNeutral);
	this->addChild(this->stateOpponentTurnStart);
	this->addChild(this->statePass);
	this->addChild(this->statePlayCard);
	this->addChild(this->statePlayerTurnStart);
	this->addChild(this->stateRoundEnd);
	this->addChild(this->stateRoundStart);
	this->addChild(this->stateSelectionStaged);
	this->addChild(this->stateTurnEnd);
	this->addChild(this->stateTutorial);
	this->addChild(this->debugDisplay);
	this->addChild(this->tutorialAIntroSequence);
	this->addChild(this->tutorialAVictory);
	this->addChild(this->tutorialAWinningRound);
	this->addChild(this->cardReplaceBanner);
	this->addChild(this->opponentFirstBanner);
	this->addChild(this->opponentLastStandBanner);
	this->addChild(this->opponentPassBanner);
	this->addChild(this->opponentRoundWinBanner);
	this->addChild(this->opponentTurnBanner);
	this->addChild(this->playerFirstBanner);
	this->addChild(this->playerLastStandBanner);
	this->addChild(this->playerPassBanner);
	this->addChild(this->playerRoundWinBanner);
	this->addChild(this->playerTurnBanner);
	this->addChild(this->roundBanner);
	this->addChild(this->roundTieBanner);
	this->addChild(this->victoryBanner);
	this->addChild(this->defeatBanner);
	this->addChild(this->drawBanner);
	this->addChild(this->menuBackDrop);
	this->addChild(this->pauseMenu);
	this->addChild(this->optionsMenu);
	this->addChild(this->confirmationMenu);
	this->addChild(Mouse::create());
}

Hexus::~Hexus()
{
}

void Hexus::onEnter()
{
	FadeScene::onEnter();

	SoundManager::playMusicResource(Resources::Music_LastMarch);

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
	this->confirmationMenu->setVisible(false); 

	GameState::updateState(this->gameState, GameState::StateType::GameStart);
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

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(Hexus::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(Hexus::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(Hexus::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(Hexus::onExitClick, this));

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
		{
			event->stopPropagation();
			this->openPauseMenu();
			break;
		}
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			// this->gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(true, this->gameState->opponentData, 0));
			break;
		}
		default:
		{
			break;
		}
	}
}

void Hexus::onOptionsExit()
{
	this->optionsMenu->setVisible(false);
	this->openPauseMenu();
}

void Hexus::openPauseMenu()
{
	this->menuBackDrop->setOpacity(196);
	this->pauseMenu->setVisible(true);
	GameUtils::focus(this->pauseMenu);
}

void Hexus::onResumeClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	GameUtils::focus(this);
}

void Hexus::onOptionsClick()
{
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(true);
	GameUtils::focus(this->optionsMenu);
}

void Hexus::onExitClick()
{
	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	NavigationEvents::navigate(NavigationEvents::GameScreen::Title);
}
