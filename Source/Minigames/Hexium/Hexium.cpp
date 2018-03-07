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

	this->playerFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->playerPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->playerPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);

	this->enemyFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->enemyPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->enemyPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);

	this->playerDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->playerDeckCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->playerDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->enemyDeckCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->enemyDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->playerHandCardIcon = Sprite::create(Resources::Minigames_Hexium_CardIcons);
	this->playerHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->playerHandCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->playerHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyHandCardIcon = Sprite::create(Resources::Minigames_Hexium_CardIcons);
	this->enemyHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->enemyHandCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->enemyHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyBinaryCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->enemyBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyDecimalCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->enemyDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->enemyHexCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->enemyHexCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerBinaryCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->playerBinaryCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerDecimalCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->playerDecimalCardTotal->enableOutline(Color4B::BLACK, 3);
	this->playerHexCardTotal = Label::create("", Resources::Fonts_UbuntuMono_B, 48.0f);
	this->playerHexCardTotal->enableOutline(Color4B::BLACK, 3);

	this->playerPadDeck->setScale(Card::cardScale);
	this->playerPadGrave->setScale(Card::cardScale);
	this->enemyPadDeck->setScale(Card::cardScale);
	this->enemyPadGrave->setScale(Card::cardScale);

	this->statusBanner = LayerColor::create(Color4B(0, 0, 0, 127), 1920.0f, 144.0f);
	this->statusLabel = Label::create("", Resources::Fonts_Montserrat_Medium, 48.0f);

	this->statusBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusBanner->setOpacity(0);
	this->statusLabel->setOpacity(0);

	this->addChild(this->gameBackground);
	this->addChild(this->playerFrame);
	this->addChild(this->enemyFrame);
	this->addChild(this->playerPadDeck);
	this->addChild(this->playerPadGrave);
	this->addChild(this->enemyPadDeck);
	this->addChild(this->enemyPadGrave);

	this->addChild(this->playerDeckCardCountFrame);
	this->addChild(this->playerDeckCardCountText);
	this->addChild(this->enemyDeckCardCountFrame);
	this->addChild(this->enemyDeckCardCountText);

	this->addChild(this->playerHandCardCountFrame);
	this->addChild(this->playerHandCardIcon);
	this->addChild(this->playerHandCardCountText);

	this->addChild(this->enemyHandCardCountFrame);
	this->addChild(this->enemyHandCardIcon);
	this->addChild(this->enemyHandCardCountText);

	this->addChild(this->enemyBinaryCardTotal);
	this->addChild(this->enemyDecimalCardTotal);
	this->addChild(this->enemyHexCardTotal);
	this->addChild(this->playerBinaryCardTotal);
	this->addChild(this->playerDecimalCardTotal);
	this->addChild(this->playerHexCardTotal);

	this->addChild(this->statusBanner);
	this->addChild(this->statusLabel);
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

	this->doCoinFlipAnimation();
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->playerFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->enemyFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
	this->playerPadDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY);
	this->playerPadGrave->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::graveyardOffsetY);
	this->enemyPadDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY);
	this->enemyPadGrave->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::graveyardOffsetY);

	this->playerDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY - 32.0f);
	this->playerDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY);

	this->enemyDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY);
	this->enemyDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY + 32.0f);

	this->playerHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f - Config::handCountOffsetY - 32.0f);
	this->playerHandCardIcon->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 40.0f, visibleSize.height / 2.0f - Config::handCountOffsetY - 16.0f);
	this->playerHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::handCountOffsetY);

	this->enemyHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f + Config::handCountOffsetY);
	this->enemyHandCardIcon->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 40.0f, visibleSize.height / 2.0f + Config::handCountOffsetY + 16.0f);
	this->enemyHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::handCountOffsetY + 32.0f);

	this->playerBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY - 0.0f);
	this->playerDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY - 0.0f);
	this->playerHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY - 0.0f);

	this->enemyBinaryCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY + 0.0f);
	this->enemyDecimalCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY + 0.0f);
	this->enemyHexCardTotal->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY + 0.0f);

	this->statusBanner->setPosition(0.0f, visibleSize.height / 2.0f - this->statusBanner->getContentSize().height / 2 + 320.0f);
	this->statusLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
}

void Hexium::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);
	/*this->gameState->setCardPreviewCallback(CC_CALLBACK_1(Hexium::previewCard, this));
	this->gameState->setUpdateStateCallback(CC_CALLBACK_1(Hexium::updateDisplayState, this));
	this->gameState->setEndTurnCallback(CC_CALLBACK_0(Hexium::displayTurnBanner, this));
	this->gameState->setRequestAiCallback(Ai::performAiActions);*/

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onGameStart(EventCustom* eventCustom)
{
	Hexium::HexiumGameEventArgs* args = (Hexium::HexiumGameEventArgs*)(eventCustom->getUserData());

	GameState::updateState(this->gameState, GameState::StateType::CoinFlip);
	//this->gameState->gameStart(args->playerDeck, args->enemyDeck);
	this->updateDisplayState(false);

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


void Hexium::updateDisplayState(bool prePlayerDraw)
{
	// Note: If updating state right before player draw, add +1 because the insert is delayed because of the animation
	int playerHandCount = prePlayerDraw ? this->gameState->playerHand->getCardCount() + 1 : this->gameState->playerHand->getCardCount();

	this->playerDeckCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->playerDeck->getCardCount(), 2));
	this->enemyDeckCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->enemyDeck->getCardCount(), 2));
	this->playerHandCardCountText->setString(StrUtils::toStringZeroPad(playerHandCount, 2));
	this->enemyHandCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->enemyHand->getCardCount(), 2));

	this->playerBinaryCardTotal->setString(std::to_string(this->gameState->playerBinaryCards->getRowAttack()));
	this->playerDecimalCardTotal->setString(std::to_string(this->gameState->playerDecimalCards->getRowAttack()));
	this->playerHexCardTotal->setString(std::to_string(this->gameState->playerHexCards->getRowAttack()));
	this->enemyBinaryCardTotal->setString(std::to_string(this->gameState->enemyBinaryCards->getRowAttack()));
	this->enemyDecimalCardTotal->setString(std::to_string(this->gameState->enemyDecimalCards->getRowAttack()));
	this->enemyHexCardTotal->setString(std::to_string(this->gameState->enemyHexCards->getRowAttack()));
}

void Hexium::displayStatusBannerMessage(std::string message)
{
	this->statusLabel->setString(message);

	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 127),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
}

void Hexium::displayTurnBanner()
{
	switch (this->gameState->turn)
	{
	case GameState::Turn::Player:
		this->displayStatusBannerMessage("YOUR TURN");
		break;
	case GameState::Turn::Enemy:
		break;
	}
}

/*
GameState::GameState()
{
this->stagedSacrifice = nullptr;
this->selectedCard = nullptr;
this->updateStateCallback = nullptr;
this->endTurnCallback = nullptr;
this->cardPreviewCallback = nullptr;
this->requestAiCallback = nullptr;
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
if (card != this->selectedCard)
{
this->selectCard(card);
}
else
{
this->cancelCurrentAction(true);
}
}

void GameState::selectCard(Card* card)
{
if (this->selectedCard != nullptr)
{
this->cancelCurrentAction(false);
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
this->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
break;
case CardData::CardType::Decimal:
this->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
break;
case CardData::CardType::Hexidecimal:
this->playerHexCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
break;
case CardData::CardType::Special_SHL:
case CardData::CardType::Special_SHR:
case CardData::CardType::Special_FLIP1:
case CardData::CardType::Special_FLIP2:
case CardData::CardType::Special_FLIP3:
case CardData::CardType::Special_FLIP4:
case CardData::CardType::Special_INV:
this->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
this->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
this->playerHexCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
this->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
this->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
this->enemyHexCards->enableRowSelection(CC_CALLBACK_1(GameState::playSelectedCard, this));
break;
case CardData::CardType::Special_AND:
case CardData::CardType::Special_OR:
case CardData::CardType::Special_XOR:
case CardData::CardType::Special_ADD:
case CardData::CardType::Special_SUB:
case CardData::CardType::Special:
this->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(GameState::stageSelectedSacrificeCard, this));
this->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(GameState::stageSelectedSacrificeCard, this));
this->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(GameState::stageSelectedSacrificeCard, this));
break;
}
}

void GameState::cancelCurrentAction(bool clearSelectedCard)
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
case CardData::CardType::Special_SHL:
case CardData::CardType::Special_SHR:
case CardData::CardType::Special_FLIP1:
case CardData::CardType::Special_FLIP2:
case CardData::CardType::Special_FLIP3:
case CardData::CardType::Special_FLIP4:
case CardData::CardType::Special_INV:
this->playerBinaryCards->disableRowSelection();
this->playerDecimalCards->disableRowSelection();
this->playerHexCards->disableRowSelection();
this->enemyBinaryCards->disableRowSelection();
this->enemyDecimalCards->disableRowSelection();
this->enemyHexCards->disableRowSelection();
break;
case CardData::CardType::Special_AND:
case CardData::CardType::Special_OR:
case CardData::CardType::Special_XOR:
case CardData::CardType::Special_ADD:
case CardData::CardType::Special_SUB:
case CardData::CardType::Special:
this->playerBinaryCards->disableRowSelection();
this->playerDecimalCards->disableRowSelection();
this->playerHexCards->disableRowSelection();
break;
}

if (clearSelectedCard)
{
this->selectCard(nullptr);
}
}
}

void GameState::onRowCardClick(Card* card)
{
// TODO: potentially store up xor/and/or targets if one is queued up
}

void GameState::playSelectedCard(CardRow* cardRow)
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
case CardData::CardType::Special_SHL:
case CardData::CardType::Special_SHR:
case CardData::CardType::Special_FLIP1:
case CardData::CardType::Special_FLIP2:
case CardData::CardType::Special_FLIP3:
case CardData::CardType::Special_FLIP4:
case CardData::CardType::Special_INV:
this->playerHand->removeCard(this->selectedCard);
this->selectedCard->disableInteraction();
this->playerGraveyard->insertCardTop(this->selectedCard, true, Config::insertDelay);

Card::Operation operation = Card::toOperation(this->selectedCard->cardData->cardType, 0);

for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
{
Card* card = *it;

card->addOperation(operation);
}

this->playerBinaryCards->disableRowSelection();
this->playerDecimalCards->disableRowSelection();
this->playerHexCards->disableRowSelection();
this->enemyBinaryCards->disableRowSelection();
this->enemyDecimalCards->disableRowSelection();
this->enemyHexCards->disableRowSelection();
this->endTurn();
break;
}

this->selectedCard = nullptr;
}

void GameState::stageSelectedSacrificeCard(Card* card)
{
if (this->selectedCard == nullptr)
{
return;
}

switch (this->selectedCard->cardData->cardType) {
case CardData::CardType::Special_AND:
case CardData::CardType::Special_OR:
case CardData::CardType::Special_XOR:
case CardData::CardType::Special_ADD:
case CardData::CardType::Special_SUB:
this->stagedSacrifice = card;
this->playerHand->removeCard(this->selectedCard);
this->selectedCard->disableInteraction();
this->playerGraveyard->insertCardTop(this->selectedCard, true, Config::insertDelay);

Card::Operation operation = Card::toOperation(this->selectedCard->cardData->cardType, 0);

for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
{
Card* card = *it;

card->addOperation(operation);
}

this->playerBinaryCards->disableRowSelection();
this->playerDecimalCards->disableRowSelection();
this->playerHexCards->disableRowSelection();
this->enemyBinaryCards->disableRowSelection();
this->enemyDecimalCards->disableRowSelection();
this->enemyHexCards->disableRowSelection();
this->endTurn();
break;
}

this->selectedCard = nullptr;
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

*/