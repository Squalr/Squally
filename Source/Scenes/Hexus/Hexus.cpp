#include "Hexus.h"

Hexus* Hexus::instance = nullptr;

void Hexus::registerGlobalScene()
{
	if (Hexus::instance == nullptr)
	{
		Hexus::instance = new Hexus();
		Hexus::instance->autorelease();
		Hexus::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(Hexus::instance);
}

Hexus::Hexus()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground = Sprite::create(HexusResources::Gameboard);
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
	this->tutorialBIntroSequence = TutorialBIntroSequence::create();
	this->tutorialCIntroSequence = TutorialCIntroSequence::create();
	this->tutorialDIntroSequence = TutorialDIntroSequence::create();
	this->tutorialEIntroSequence = TutorialEIntroSequence::create();
	this->tutorialFIntroSequence = TutorialFIntroSequence::create();
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
	this->gameState->passButtonPointer = this->statePass->passButton;
	this->gameState->lastStandButtonPointer = this->statePass->lastStandButton;
	this->gameState->claimVictoryButtonPointer = this->statePass->claimVictoryButton;

	this->addChild(this->gameBackground);
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
	this->addChild(this->gameState);
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
	this->addChild(this->tutorialBIntroSequence);
	this->addChild(this->tutorialCIntroSequence);
	this->addChild(this->tutorialDIntroSequence);
	this->addChild(this->tutorialEIntroSequence);
	this->addChild(this->tutorialFIntroSequence);
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
}

Hexus::~Hexus()
{
}

void Hexus::onEnter()
{
	GlobalScene::onEnter();

	SoundManager::playMusicResource(MusicResources::LastMarch);

	this->menuBackDrop->setOpacity(0);
	this->pauseMenu->setVisible(false);
	this->optionsMenu->setVisible(false);
	this->confirmationMenu->setVisible(false); 

	GameState::updateState(this->gameState, GameState::StateType::GameStart);
}

void Hexus::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
}

void Hexus::initializeListeners()
{
	GlobalScene::initializeListeners();

	Hexus::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexus, [](EventCustom* args)
	{
		NavigationEvents::NavigateHexusArgs* hexusArgs = static_cast<NavigationEvents::NavigateHexusArgs*>(args->getUserData());

		if (hexusArgs != nullptr)
		{
			Hexus::instance->startGame(hexusArgs->opponentData);
			GlobalDirector::loadScene(Hexus::instance);
		}
	}));
	
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Hexus::onKeyPressed, this);

	this->optionsMenu->setBackClickCallback(CC_CALLBACK_0(Hexus::onOptionsExit, this));
	this->pauseMenu->setResumeCallback(CC_CALLBACK_0(Hexus::onResumeClick, this));
	this->pauseMenu->setOptionsCallback(CC_CALLBACK_0(Hexus::onOptionsClick, this));
	this->pauseMenu->setExitCallback(CC_CALLBACK_0(Hexus::onExitClick, this));

	this->addEventListener(keyboardListener);
}

void Hexus::startGame(HexusOpponentData* opponentData)
{
	this->gameState->opponentData = opponentData;

	this->gameState->previousStateType = GameState::StateType::EmptyState;
	this->gameState->stateType = GameState::StateType::EmptyState;

	this->avatars->initializeEnemyAvatar(opponentData);

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

	opponentData->getDeck()->copyTo(this->gameState->enemyDeck);
	Deck::create(Card::CardStyle::Earth, CardStorage::getInstance()->getDeckCards())->copyTo(this->gameState->playerDeck);
}

void Hexus::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
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
	NavigationEvents::navigateTitle();
}
