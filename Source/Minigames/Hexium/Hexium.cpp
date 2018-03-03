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
	this->emblem = Sprite::create(Resources::Minigames_Hexium_Emblem);

	this->gameState = GameState::create();

	this->previewPanel = Node::create();
	this->currentPreviewCard = nullptr;

	this->playerFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->playerPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->playerPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->playerSocketA = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->playerSocketB = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->playerSkullA = Sprite::create(Resources::Minigames_Hexium_Skull);
	this->playerSkullB = Sprite::create(Resources::Minigames_Hexium_Skull);

	this->enemyFrame = Sprite::create(Resources::Minigames_Hexium_AvatarFrame);
	this->enemyPadDeck = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->enemyPadGrave = Sprite::create(Resources::Minigames_Hexium_CardPad);
	this->enemySocketA = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->enemySocketB = Sprite::create(Resources::Minigames_Hexium_Socket);
	this->enemySkullA = Sprite::create(Resources::Minigames_Hexium_Skull);
	this->enemySkullB = Sprite::create(Resources::Minigames_Hexium_Skull);

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

	this->playerHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerHandCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->playerHandCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->playerHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyHandCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->enemyHandCardCountText = Label::create("", Resources::Fonts_UbuntuMono_B, 32.0f);
	this->enemyHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->playerPadDeck->setScale(Card::cardScale);
	this->playerPadGrave->setScale(Card::cardScale);
	this->enemyPadDeck->setScale(Card::cardScale);
	this->enemyPadGrave->setScale(Card::cardScale);

	this->addChild(this->gameBackground);
	this->addChild(this->playerFrame);
	this->addChild(this->enemyFrame);
	this->addChild(this->playerPadDeck);
	this->addChild(this->playerPadGrave);
	this->addChild(this->enemyPadDeck);
	this->addChild(this->enemyPadGrave);
	this->addChild(this->playerSocketA);
	this->addChild(this->playerSocketB);
	this->addChild(this->playerSkullA);
	this->addChild(this->playerSkullB);
	this->addChild(this->enemySocketA);
	this->addChild(this->enemySocketB);
	this->addChild(this->enemySkullA);
	this->addChild(this->enemySkullB);
	this->addChild(this->emblem);

	this->addChild(this->gameState);

	this->addChild(this->playerDeckCardCountFrame);
	this->addChild(this->playerDeckCardCountText);
	this->addChild(this->enemyDeckCardCountFrame);
	this->addChild(this->enemyDeckCardCountText);

	this->addChild(this->playerHandCardCountFrame);
	this->addChild(this->playerHandCardCountText);
	this->addChild(this->enemyHandCardCountFrame);
	this->addChild(this->enemyHandCardCountText);

	this->addChild(this->previewPanel);
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
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->emblem->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::emblemOffsetX, visibleSize.height / 2.0f);
	this->playerFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->enemyFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
	this->playerPadDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY);
	this->playerPadGrave->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::graveyardOffsetY);
	this->enemyPadDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY);
	this->enemyPadGrave->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::graveyardOffsetY);
	this->playerSocketA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSocketB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSkullA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->playerSkullB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f - Config::socketOffsetY);
	this->enemySocketA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySocketB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySkullA->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketAOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);
	this->enemySkullB->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::socketBOffsetX, visibleSize.height / 2.0f + Config::socketOffsetY);

	this->playerDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::labelsOffsetY - 32.0f);
	this->playerDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::deckOffsetY + 32.0f - Config::labelsOffsetY - 32.0f);
	this->enemyDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::labelsOffsetY);
	this->enemyDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::deckOffsetY + 32.0f + Config::labelsOffsetY);

	this->playerHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f - Config::deckOffsetY + Config::labelsOffsetY);
	this->playerHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::deckOffsetY + 32.0f + Config::labelsOffsetY);
	this->enemyHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f + Config::deckOffsetY - Config::labelsOffsetY - 32.0f);
	this->enemyHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::deckOffsetY - Config::labelsOffsetY);

	this->previewPanel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter, visibleSize.height / 2.0f + Config::previewOffsetY);
}

void Hexium::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);
	this->gameState->setCardPreviewCallback(CC_CALLBACK_1(Hexium::previewCard, this));
	this->gameState->setUpdateStateCallback(CC_CALLBACK_1(Hexium::updateDisplayState, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onGameStart(EventCustom* eventCustom)
{
	Hexium::HexiumGameEventArgs* args = (Hexium::HexiumGameEventArgs*)(eventCustom->getUserData());

	this->gameState->gameStart(args->playerDeck, args->enemyDeck);

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
		GameUtils::navigateBack();
		event->stopPropagation();
		break;
	}
}

void Hexium::onClose(MenuSprite* menuSprite)
{
	GameUtils::navigateBack();
}

void Hexium::previewCard(Card* card)
{
	if (card != this->currentPreviewCard)
	{
		this->currentPreviewCard = card;

		this->previewPanel->removeAllChildren();

		Sprite* previewSprite = Sprite::create(card->cardData->cardResourceFile);
		this->previewPanel->addChild(previewSprite);

		switch (card->cardData->cardType) {
		case CardData::CardType::Decimal:
		case CardData::CardType::Binary:
		case CardData::CardType::Hexidecimal:
		{
			int attack = card->getAttack();

			Label* binaryLabel = Label::create("BIN: " + HackUtils::toBinary4(attack), Resources::Fonts_UbuntuMono_B, 32);
			Label* decimalLabel = Label::create("DEC: " + std::to_string(attack), Resources::Fonts_UbuntuMono_B, 32);
			Label* hexLabel = Label::create("HEX: " + HackUtils::toHex(attack), Resources::Fonts_UbuntuMono_B, 32);

			binaryLabel->setAnchorPoint(Vec2::ZERO);
			decimalLabel->setAnchorPoint(Vec2::ZERO);
			hexLabel->setAnchorPoint(Vec2::ZERO);

			binaryLabel->setTextColor(Card::binaryColor);
			decimalLabel->setTextColor(Card::decimalColor);
			hexLabel->setTextColor(Card::hexColor);

			binaryLabel->enableOutline(Color4B::BLACK, 3);
			decimalLabel->enableOutline(Color4B::BLACK, 3);
			hexLabel->enableOutline(Color4B::BLACK, 3);

			binaryLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f));
			decimalLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f - 40.0f));
			hexLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f + 8.0f, -212.0f - 80.0f));

			this->previewPanel->addChild(binaryLabel);
			this->previewPanel->addChild(decimalLabel);
			this->previewPanel->addChild(hexLabel);
		}
		break;
		default:
		{
			Label * specialLabel = Label::create("", Resources::Fonts_UbuntuMono_B, 28);

			specialLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
			specialLabel->setTextColor(Card::specialColor);
			specialLabel->enableOutline(Color4B::BLACK, 2);
			specialLabel->setPosition(Vec2(-previewSprite->getContentSize().width / 2.0f - 32.0f, -172.0f));
			specialLabel->setDimensions(previewSprite->getContentSize().width + 64.0f, 0.0f);

			switch (card->cardData->cardType) {
			case CardData::CardType::Special_AND:
				specialLabel->setString("Sacrifice one of your cards on the field and AND it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_OR:
				specialLabel->setString("Sacrifice one of your cards on the field and OR it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_XOR:
				specialLabel->setString("Sacrifice one of your cards on the field and XOR it with all cards in a row of the same type.");
				break;
			case CardData::CardType::Special_SHL:
				specialLabel->setString("Shift the bits left of all cards in a row .");
				break;
			case CardData::CardType::Special_SHR:
				specialLabel->setString("Shift the bits right of all cards in a row.");
				break;
			case CardData::CardType::Special_INV:
				specialLabel->setString("Invert all bits in a row.");
				break;
			case CardData::CardType::Special_FLIP1:
				specialLabel->setString("Flip the 1st bit of all cards in a row.");
				break;
			case CardData::CardType::Special_FLIP2:
				specialLabel->setString("Flip the 2nd bit of all cards in a row.");
				break;
			case CardData::CardType::Special_FLIP3:
				specialLabel->setString("Flip the 3rd bit of all cards in a row.");
				break;
			case CardData::CardType::Special_FLIP4:
				specialLabel->setString("Flip the 4th bit of all cards in a row.");
				break;
			case CardData::CardType::Special_ADD:
				specialLabel->setString("Sacrifice one of your cards on the field and ADD it to two cards of the same type.");
				break;
			case CardData::CardType::Special_SUB:
				specialLabel->setString("Sacrifice one of your cards on the field and SUB it from two cards of the same type.");
				break;
			case CardData::CardType::Special:
				specialLabel->setString("???.");
				break;
			default:
				break;
			}

			this->previewPanel->addChild(specialLabel);
			break;
		}
		}
	}
}

void Hexium::updateDisplayState(bool prePlayerDraw)
{
	// Note: If updating state right before player draw, add +1 because the insert is delayed because of the animation
	int playerHandCount = prePlayerDraw ? this->gameState->playerHand->getCardCount() + 1 : this->gameState->playerHand->getCardCount();

	this->playerDeckCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->playerDeck->getCardCount(), 2));
	this->enemyDeckCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->enemyDeck->getCardCount(), 2));
	this->playerHandCardCountText->setString(StrUtils::toStringZeroPad(playerHandCount, 2));
	this->enemyHandCardCountText->setString(StrUtils::toStringZeroPad(this->gameState->enemyHand->getCardCount(), 2));
}