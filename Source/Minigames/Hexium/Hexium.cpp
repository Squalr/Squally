#include "Hexium.h"

const std::string Hexium::HexiumGameStartEvent = "hexium_game_start_event";
const std::string Hexium::HexiumGameEndEvent = "hexium_game_end_event";

Hexium* Hexium::create()
{
	Hexium* hexium = new Hexium();

	hexium->autorelease();

	return hexium;
}

Hexium::Hexium()
{
	this->gameBackground = Sprite::create(Resources::Minigames_Hexium_Gameboard);
	this->gameState = GameState::create();
	this->avatars = Avatars::create();
	this->banners = Banners::create();
	this->cardPreview = CardPreview::create();
	this->controlDraw = ControlDraw::create();
	this->controlNeutral = ControlNeutral::create();
	this->controlEndTurn = ControlEndTurn::create();
	this->controlSacrificeStaged = ControlSacrificeStaged::create();
	this->controlSelectionStaged = ControlSelectionStaged::create();
	this->controlReplaceCards = ControlReplaceCards::create();
	this->coinFlip = CoinFlip::create();
	this->deckCardCountDisplay = DeckCardCountDisplay::create();
	this->handCardCountDisplay = HandCardCountDisplay::create();
	this->lossesDisplay = LossesDisplay::create();
	this->rowTotals = RowTotals::create();
	this->scoreTotal = ScoreTotal::create();

	this->addChild(this->gameBackground);
	this->addChild(this->gameState);
	this->addChild(this->avatars);
	this->addChild(this->controlDraw);
	this->addChild(this->controlNeutral);
	this->addChild(this->controlSelectionStaged);
	this->addChild(this->controlSacrificeStaged);
	this->addChild(this->controlReplaceCards);
	this->addChild(this->controlEndTurn);
	this->addChild(this->cardPreview);
	this->addChild(this->lossesDisplay);
	this->addChild(this->deckCardCountDisplay);
	this->addChild(this->handCardCountDisplay);
	this->addChild(this->rowTotals);
	this->addChild(this->scoreTotal);
	this->addChild(this->coinFlip);
	this->addChild(this->banners);
}

Hexium::~Hexium()
{
}

void Hexium::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();
	this->initializeListeners();
	this->addChild(Mouse::claimInstance());

	GameState::updateState(this->gameState, GameState::StateType::DrawInitialCards);
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
}

void Hexium::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onGameStart(EventCustom* eventCustom)
{
	Hexium::HexiumGameEventArgs* args = (Hexium::HexiumGameEventArgs*)(eventCustom->getUserData());

	this->gameState->playerLosses = 0;
	this->gameState->enemyLosses = 0;

	this->gameState->playerGraveyard->clear();
	this->gameState->enemyGraveyard->clear();
	this->gameState->playerHand->clear();
	this->gameState->enemyHand->clear();
	this->gameState->playerDeck->clear();
	this->gameState->enemyDeck->clear();

	args->playerDeck->copyTo(this->gameState->playerDeck);
	args->enemyDeck->copyTo(this->gameState->enemyDeck);

	GameUtils::navigate(GameUtils::GameScreen::Hexium);
}

void Hexium::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
	}
}

void Hexium::onClose(MenuSprite* menuSprite)
{
	GameUtils::navigateBack();
}
